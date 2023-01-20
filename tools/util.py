import copy

class mkstr:
    def __init__(self, str):
        self.str = str

    def __call__(self, targets, source, env):
        return self.str

    def __str__(self):
        return self.str

def contains_any(needles, haystack):
    """ Returns True if any of the needles are in haystack

    >>> contains_any([1, 2, 3], [50, 37, 12, 1])
    True
    >>> contains_any([1, 2, 3], [50, 37, 12])
    False
    """
    for needle in needles:
        if needle in haystack:
            return True
    return False

def list2str(list):
    """Given a list return a string"""
    return "[" + ", ".join([str(x) for x in list]) + "]"

def make_global(obj, name=None):
    """ Inserts an object into the global namespace. By default
    the name is determined by the objects __name__ attribute. Alternatively
    a name can be specified.

    >>> make_global(1, "One")
    >>> One
    1
    """
    if name:
        globals()[name] = obj
    else:
        globals()[obj.__name__] = obj

class IdentityMapping:
    """ This is an object that can be used to generate an identity mapping.
    That is it is an object that has the same interface as a normal dictionary,
    but every lookup returns the key itself. E.g:

    >>> identity_mapping = IdentityMapping()
    >>> identity_mapping[1]
    1
    >>> identity_mapping["foo"]
    'foo'
    """
    def __getitem__(self, key):
        return key

identity_mapping = IdentityMapping()

class OrderedDict:
    """A very simple insertion ordered dictionary so we can gets
    out keys in insertion order. This is used because we need to link
    against libraries in the order in which the are added"""
    
    def __init__(self):
        self.dict = {}
        self.insert_order = []

    def __setitem__(self, key, value):
        self.dict[key] = value
        self.insert_order.append(key)

    def __getitem__(self, key):
        return self.dict[key]

    def keys(self):
        return self.insert_order

    def __copy__(self):
        new = OrderedDict()
        new.dict = copy.copy(self.dict)
        new.insert_order = copy.copy(self.insert_order)
        return new

class ListFunction:
    def __init__(self, fn):
        self.fn = fn

    def __getitem__(self, idx):
        return self.fn()[idx]
