#!/usr/bin/env python3
"""
IEF, ETH Zürich
Author(s): Dominik Werner, Patrick Wintermeyer

"""


class ObservableList(list):
    """This list can send notifications about changes.

    Attributes
    ----------
    item_added : list
        Callback list for add events.
    item_removed : list
        Callback list for remove events.
    on_clear : list
        Callback list for clear events.
    """

    def __init__(self, *args, **kwargs):
        """Constructor.

        Parameters
        ----------
        *args
            Arguments passed to constructor. Delegated to superclass.
        **kwargs
            Keywords passed to constructor. Delegated to superclass.
        """
        super(ObservableList, self).__init__(*args, **kwargs)
        self.item_added = list()
        self.item_removed = list()
        self.on_clear = list()

    def append(self, item):
        """Append item to the list and trigger notification.

        Parameters
        ----------
        item : variable type
            Item to be added to the list.
        """
        super(ObservableList, self).append(item)

        # execute all subscribed callback methods
        for callback in self.item_added:
            callback(item)

    def remove(self, item):
        """Remove item from the list and trigger notification.

        Parameters
        ----------
        item : variable type
            Item to be removed from the list.
        """
        super(ObservableList, self).remove(item)

        # execute all subscribed callback methods
        for callback in self.item_removed:
            callback(item)

    def clear(self):
        """Remove all items from the list and trigger notification.
        """
        super(ObservableList, self).clear()

        # execute all subscribed callback methods
        for callback in self.on_clear:
            callback()
