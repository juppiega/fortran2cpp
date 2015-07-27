'''
Test utility.removeComment(line) function
'''
import unittest
from utility import removeComment


class Test(unittest.TestCase):


    def setUp(self):
        self.line = "   integer(kind = 8) i !LolComment"


    def testRemoveComment(self):
        c = removeComment(self.line)
        self.assertEqual(c.comment, "!LolComment")
        self.assertEqual(c.lineOnly, "integer(kind = 8) i")


if __name__ == "__main__":
    unittest.main()