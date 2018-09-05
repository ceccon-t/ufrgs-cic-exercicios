import unittest

from algoritmos_sorting import *


class SortingTest(unittest.TestCase):

    def setUp(self):
        self.sorter = SelectionSort()

    def tearDown(self):
        pass

    def areEqual(self, lst_a, lst_b):
        if len(lst_a) != len(lst_b):
            return False
        for i in range(len(lst_a)):
            if lst_a[i] != lst_b[i]:
                return False
        return True

    # Tests
    def test_empty(self):
        lst = []
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

    def test_single_element(self):
        lst = [7]
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

    def test_two_elements(self):
        lst = [9, 7]
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

    def test_multiple_elements_even(self):
        lst = [4, 6, 3, 1]
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

    def test_multiple_elements_odd(self):
        lst = [7, 4, 6, 3, 1]
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

    def test_multiple_elements_with_repetition(self):
        lst = [7, 4, 6, 4, 3, 1]
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

    def test_all_elements_equal(self):
        lst = [42, 42, 42, 42, 42, 42]
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

    def test_already_ordered(self):
        lst = [2, 3, 5, 7, 11, 13]
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

    def test_reverse_ordered(self):
        lst = [13, 11, 7, 5, 3, 2]
        sorted_lst = self.sorter.sort(lst)
        self.assertTrue(self.areEqual(sorted_lst, sorted(lst)))

