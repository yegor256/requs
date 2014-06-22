# -*- coding: utf-8 -*-

from pygments.lexer import RegexLexer
from pygments.token import Punctuation, Text, Keyword, Name, String
from pygments.util import shebang_matches

class RequsLexer(RegexLexer):
    name = 'requs'
    aliases = ['requs']
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


