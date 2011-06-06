import StringIO
import os
import unittest

from validation import write_page



class TestTracPlugin(unittest.TestCase):

    def testDummyWritePage(self):
        self.assertTrue(True)
        io = StringIO.StringIO()
        lines = ['line1', 'line2', 'line3']
        write_page(io, 'name', '\n'.join(lines))
        text = """name\n%d\n%s\n""" % (len(lines), '\n'.join(lines))
        self.assertEqual(io.getvalue(), text)

if __name__ == '__main__':

    # If we need to log errors we should redirect stderr to stdout here,
    # because maven convert 2>&1 arg to "2>&1" and python use it as own arg
    # os.dup2(1, 2)
    unittest.main()
