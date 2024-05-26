# -*- coding: utf-8 -*-

from pygments.lexer import RegexLexer
from pygments.token import Punctuation, Text, Keyword, Name, String, Operator
from pygments.util import shebang_matches


class RequsLexer(RegexLexer):
    name = 'requs'
    aliases = ['requs']
    tokens = {
        'root': [
            (r'"""[\n.]+"""', Text),
            (r'"[^"]+"', String),
            (
                r'\b(includes|requires|contains|actor|needs|means|using|of|with|when|must|is|a|(T|t)he|as|where|and)\b',
                Keyword,
            ),
            (r'\b(creates|reads|updates|deletes|Fail\s+since)\b', Operator),
            (r'\b[A-Z]+\b', Name),
            (r'\b([A-Z][a-z0-9]*)+\b', Name),
            (r'[,;:]', Punctuation),
        ],
    }

    def analyse_text(text):
        return shebang_matches(text, r'requs')
