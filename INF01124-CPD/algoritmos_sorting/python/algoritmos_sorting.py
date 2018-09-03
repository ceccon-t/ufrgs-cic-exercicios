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
    # and switching them if they are in order - effectively
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