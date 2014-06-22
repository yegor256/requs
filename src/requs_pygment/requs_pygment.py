# -*- coding: utf-8 -*-

import re

from pygments.lexer import Lexer, RegexLexer, do_insertions, bygroups, include
from pygments.token import Punctuation, Text, Keyword, Name, String
from pygments.util import shebang_matches

line_re  = re.compile('.*?\n')

class RequsLexer(RegexLexer):
    name = 'Requs'
    aliases = ['requs']
    filenames = ['*.req']
    mimetypes = ['application/x-requs']

    tokens = {
        'root': [
            (r'"[^"]+"', String),
            (r'""".+"""', Text),
            (r'\b(needs|includes|requires|when|fail|since|must|is|a|the)\s*\b', Keyword),
            (r'([A-Z][a-z]+)+', Name),
            (r'[,;:]', Punctuation),
        ],
    }

    def analyse_text(text):
        return shebang_matches(text, r'requs')


