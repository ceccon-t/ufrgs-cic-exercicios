import copy

class PythonDefaultSorting:
    def sort(self, lst_to_sort):
        return sorted(lst_to_sort)

class InsertionSort:
    # Assumes first part of list to be ordered
    # and then traverses second part one element
    # at a time, inserting it on the right place
    # inside ordered part.
    # Initially, first part is just the first element
    # and second part is the rest of the list.

    def sort(self, lst_to_sort):
        lst = copy.deepcopy(lst_to_sort)

        for j in range(1, len(lst)):
            value = lst[j]
            i = j - 1
            while i >= 0 and lst[i] > value:
                lst[i+1] = lst[i]
                i -= 1
            lst[i+1] = value

        return lst

class BubbleSort:
    # Traverses the entire list checking adjacent elements
    # and switching them if they are not in order - effectively
    # "bubbling" the largest ones one at a time to the end
    # of the list. Stops when after a traversal it has not
    # switched any elements, which means they are all in order.

    def sort(self, lst_to_sort):
        lst = copy.deepcopy(lst_to_sort)
        switched = True # just to set things in motion

        while switched:
            switched = False # at start no element has been switched
            for i in range(len(lst)-1):
                if lst[i] > lst[i+1]: # found one element out of order
                    aux = lst[i+1]
                    lst[i+1] = lst[i]
                    lst[i] = aux
                    switched = True

        return lst

class Quicksort:
    # Successively rearranges the list by picking a pivot element and
    # generating a new configuration where all the elements smaller than
    # this pivot are to its left and all the elements larger than it are to
    # its right, then recursively calls itself on both sides.

    def sort(self, lst_to_sort):
        lst = copy.deepcopy(lst_to_sort)

        self._Quicksort__quicksort(lst, 0, len(lst_to_sort)-1)

        return lst

    def __quicksort(self, lst_to_sort, first, last):
        pivot = self._Quicksort__choose_pivot(lst_to_sort, first, last)
        pivot_position = self._Quicksort__partition(lst_to_sort, pivot, first, last)
        if pivot_position >= 0:
            self._Quicksort__quicksort(lst_to_sort, first, pivot_position-1)
            self._Quicksort__quicksort(lst_to_sort, pivot_position+1, last)


    def __choose_pivot(self,lst_to_sort, first, last):
        # the simplest of the many possible ways to do this step is to pick the first element
        return first

    def __partition(self, lst_to_sort, pivot, first, last):
        # this method generates the next configuration of the list
        # and returns the position of the pivot in this new configuration

        if last < first: # zero element list, end of recursion
            return -1

        pivot_value = lst_to_sort[pivot]
        i = first
        j = last

        # loop to separate smaller and larger elements on their
        # respective sides of the new configuration.
        # i traverses the list from left to right looking for
        # elements larger than the pivot (which should be to its right)
        # j traverses from the opposite direction, looking for
        # elements smaller than the pivot
        # if both are found, they are swapped
        # keeps doing it until i and j cross each other
        while i <= j:
            if i != pivot and lst_to_sort[i] > pivot_value:
                while j >= i and lst_to_sort[j] > pivot_value:
                    j -= 1
                if j > i:
                    aux = lst_to_sort[j]
                    lst_to_sort[j] = lst_to_sort[i]
                    lst_to_sort[i] = aux
            i += 1

        # places pivot in its correct position in new configuration
        aux = lst_to_sort[j]
        lst_to_sort[j] = pivot_value
        lst_to_sort[pivot] = aux

        # returns new position of the pivot
        return j