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

        self.__quicksort(lst, 0, len(lst_to_sort)-1)

        return lst

    def __quicksort(self, lst_to_sort, first, last):
        pivot = self.__choose_pivot(lst_to_sort, first, last)
        pivot_position = self.__partition(lst_to_sort, pivot, first, last)
        if pivot_position >= 0:
            self.__quicksort(lst_to_sort, first, pivot_position-1)
            self.__quicksort(lst_to_sort, pivot_position+1, last)


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

class SelectionSort:
    # Traverses the entire list and, for each position,
    # finds the smallest element of the unsorted part
    # and places it in that position. Thus the part of
    # the list to the left of the current position is
    # already sorted, and the part to the right is unsorted.

    def sort(self, lst_to_sort):
        lst = copy.deepcopy(lst_to_sort)

        for i in range(len(lst)):
            smallest_value = lst[i]
            smallest_position = i
            for j in range(i+1, len(lst)):
                if lst[j] < smallest_value:
                    smallest_value = lst[j]
                    smallest_position = j
            aux = lst[i]
            lst[i] = lst[smallest_position]
            lst[smallest_position] = aux

        return lst

class Heapsort:
    # Processes the list by seeing it as if it was a 'binary tree'
    # where all the levels except the last one are completely filled
    # with the elements of the list in the order they appear.
    # Starts by generating a max-heap, a structure in which each node
    # of the tree is greater than either of its children, placing
    # its root element (which will be the largest in the list) at the very end
    # and decrementing the size of the subset of the list it is processing,
    # then corrects the violation on max-heap constraint introduced by that change
    # and repeats this change-correct loop until only one element is left
    # (the smallest one, which will be in the first position of the list by then).

    def sort(self, lst_to_sort):
        lst = copy.deepcopy(lst_to_sort)

        bound = len(lst) - 1

        self.__build_heap(lst, bound)

        while bound > 0:
            self.__heapify(lst, bound, 0)
            self.__swap(lst, 0, bound)
            bound -= 1

        return lst

    def __pos_parent(self, pos_node):
        return int( (pos_node-1) / 2)

    def __pos_left_child(self, pos_node):
        return (2 * pos_node) + 1

    def __pos_right_child(self, pos_node):
        return (2 * pos_node) + 2

    def __has_left_child(self, pos_node, bound):
        return self.__pos_left_child(pos_node) <= bound

    def __has_right_child(self, pos_node, bound):
        return self.__pos_right_child(pos_node) <= bound

    def __get_left_child(self, pos_node, heap):
        return heap[self.__pos_left_child(pos_node)]

    def __get_right_child(self, pos_node, heap):
        return heap[self.__pos_right_child(pos_node)]

    def __build_heap(self, heap, bound):
        # Generates a heap - starts in the middle because
        # leaves are already by themselves a heap
        for i in range(int(bound/2), -1, -1):
            self.__heapify(heap, bound, i)

    def __heapify(self, heap, bound, i):
        # Checks if there is a violation of the max-heap constraint
        # in the relationship between node at position i and its children
        # and, if that is the case, fixes it
        if self.__has_left_child(i, bound):
            largest_pos = self.__pos_left_child(i)
            largest_value = self.__get_left_child(i, heap)

            if self.__has_right_child(i, bound) and self.__get_right_child(i, heap) > largest_value:
                largest_pos = self.__pos_right_child(i)
                largest_value = self.__get_right_child(i, heap)

            if largest_value > heap[i]:
                self.__swap(heap, i, largest_pos)
                self.__heapify(heap, bound, largest_pos)

    def __swap(self, heap, pos_current, pos_destiny):
        aux = heap[pos_destiny]
        heap[pos_destiny] = heap[pos_current]
        heap[pos_current] = aux

class MergeSort:
    # Breaks the list into n unitary lists (which are by default sorted) and
    # works upwards from there, merging two adjacent sorted lists together,
    # ensuring that the resulting list remains ordered.

    def sort(self, lst_to_sort):
        lst = copy.deepcopy(lst_to_sort)

        self.mergesort(lst, 0, len(lst))

        return lst

    def mergesort(self, lst, first, last):
        if (last - first) > 1:
            middle = (first + last) // 2
            self.mergesort(lst, first, middle)
            self.mergesort(lst, middle, last)
            self.merge(lst, first, lst[first:middle], lst[middle:last])

    def merge(self, lst, start, lst1, lst2):
        # Given two adjacent sorted sub-lists inside of a list,
        # merge them placing the result back inside the main list.
        i = 0
        j = 0
        current = start
        end_lst1 = len(lst1)
        end_lst2 = len(lst2)

        while i < end_lst1 and j < end_lst2:
            if lst1[i] <= lst2[j]:
                lst[current] = lst1[i]
                i += 1
            else:
                lst[current] = lst2[j]
                j += 1
            current += 1

        while i < end_lst1:
            lst[current] = lst1[i]
            i += 1
            current += 1

        while j < end_lst2:
            lst[current] = lst2[j]
            j += i
            current += 1

