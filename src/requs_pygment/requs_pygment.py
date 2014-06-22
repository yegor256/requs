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
            (r'\b(includes|requires|contains|needs|using|of|with|when|must|is|a|(T|t)he|as|where|and)\b', Keyword),
            (r'\b(creates|reads|updates|deletes|lists|Fail\s+since)\b', Operator),
            (r'([A-Z][a-z]+)+', Name),
            (r'[,;:]', Punctuation),
        ],
    }
    def analyse_text(text):
        return shebang_matches(text, r'requs')


