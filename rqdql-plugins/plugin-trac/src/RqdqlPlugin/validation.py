# coding: utf-8

import re
from subprocess import Popen, PIPE
from tempfile import TemporaryFile

from trac.core import Component, implements
from trac.web.api import IRequestFilter
from trac.wiki.api import IWikiPageManipulator, WikiSystem
from trac.wiki.model import WikiPage
from trac.wiki.web_ui import WikiModule
from trac.config import Option, BoolOption

from config import WIKI_CONTENT_TYPE
from config import WIKI_CHECK_ALL
from config import PRE_COMMIT_HOOK
from config import PRE_RENDER_HOOK

def write_page(stdin, name, text):
    lines = text.split("\n")
    stdin.write(name)
    stdin.write("\n")
    length = len(lines)
    stdin.write(str(length))
    if length > 0:
        stdin.write("\n")
        for l in lines:
            stdin.write(l.replace("\r", " ").encode("utf-8"))
            stdin.write("\n")
    stdin.flush()

class WikiPreCommitHook(Component):
    implements(IWikiPageManipulator)

    hook_path = Option("rqdql", "pre_commit_hook", PRE_COMMIT_HOOK)
    check_all = BoolOption("rqdql", "check_all", WIKI_CHECK_ALL)

    def prepare_wiki_page(*args):
        pass

    def validate_wiki_page(self, request, page):
        stdin = TemporaryFile()

        # current page
        stdin.write(request.args['comment'])
        stdin.write("\n")
        write_page(stdin, page.name, request.args['text'])

        # entire wiki
        if self.check_all:
            env = page.env
            wiki = WikiSystem(env)
            for name in wiki.get_pages():
                p = WikiPage(env, name)
                write_page(stdin, p.name, p.text)

        # communicate with hook script
        stdin.seek(0)
        try:
            proc = Popen(self.hook_path, stdin=stdin, stdout=PIPE, stderr=PIPE)
            result = [x for x in proc.stdout.readlines()]
            result.extend([x for x in proc.stderr.readlines()])
        except OSError:
            result = ["Pre-commit hook's script is not configured"]
        stdin.close()

        # push validation results into warning message
        # and prevent saving the page if the results is not empty
        if len(result) > 10:
            cdr_len = len(result) - 10
            result = result[:10]
            result.append("Other %s errors skipped" % cdr_len)

        for item in result:
            fd = tuple(item.split(":", 1))
            fd = len(fd) == 2 and fd or (None, fd[0])
            yield fd

class WikiPreRenderHook(Component):
    implements(IWikiPageManipulator)

    hook_path = Option("rqdql", "pre_render_hook", PRE_RENDER_HOOK)
    check_all = BoolOption("rqdql", "check_all", WIKI_CHECK_ALL)

    def prepare_wiki_page(self, req, page, fields):
        stdin = TemporaryFile()

        # current page
        write_page(stdin, page.name, page.text)

        # entire wiki
        if self.check_all:
            env = page.env
            wiki = WikiSystem(env)
            for name in wiki.get_pages():
                p = WikiPage(env, name)
                write_page(stdin, p.name, p.text)

        # communicate with hook script
        stdin.seek(0)
        try:
            proc = Popen(self.hook_path, stdin=stdin, stdout=PIPE, stderr=PIPE)
            result = [x.decode("utf8") for x in proc.stdout.readlines()]
            errs = [x.decode("utf8") for x in proc.stderr.readlines()]
            if len(errs):
                result = errs
        except OSError:
            result = ["Pre-render hook's script is not configured"]
        except TypeError:
            result = ["Error. Maybe, pre-render hook's script is not configured."]
        stdin.close()

        result = u''.join(result);
        fields['text'] = result;

        # Wiki page does not exists
        if not page.exists and len(result) > 0:
            page.version = 1
            page.readonly = 1

            # Light, but dirty hack: `remove` admin permissions to disappear odd
            # buttons. This modifies a private attribute `_cache` of
            # `trac.perm.PermissionCache` object.
            if 'WIKI_ADMIN' in req.perm(page.resource):
                cache = req.perm._cache
                for key, value in cache.items():
                    if 'WIKI_ADMIN' in key:
                        cache[key] = (False, value[1])

    def validate_wiki_page(*args):
        return ()

class WikiContentTypeModifier(Component):
    implements(IRequestFilter)

    content_type = Option("rqdql", "content_type", WIKI_CONTENT_TYPE)

    def pre_process_request(self, req, handler):
        return handler

    def post_process_request(self, req, template, data, content_type):
        if self.content_type:
            match = re.match(r'/wiki(?:/(.+))?$', req.path_info)
            if match and req.args.get('action', 'view') == 'view':
                content_type = self.content_type
        return (template, data, content_type)
