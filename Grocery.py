"""
Program name: Grocery.py

This script supports the Grocery C++ program by:
Returning how many times a specific item was purchased
Showing all items with their purchase counts
Creating a file with data for a bar chart

Author: Justin Aaron Turner
Creation Date: 4/13/2025
"""

class GroceryAnalyzer:
    def __init__(self, input_file='CS210_Project_Three_Input_File.txt'):
        self.input_file = input_file

    # Reads the file and returns a list of all items
    def _read_items(self):
        with open(self.input_file, 'r') as file:
            return file.read().split()

    # Returns how many times a specific item was purchased
    def specific_item_quantity(self, item_name):
        item_name = item_name.strip().lower()  # Normalize input

        items = self._read_items()
        normalized_items = [item.lower() for item in items]  # Normalize list for comparison

        if item_name in normalized_items:
            return normalized_items.count(item_name)
        else:
            return -1  # Item not found

    # Prints all items and how many times each was purchased
    def all_item_quantities(self):
        items = self._read_items()
        unique_items = sorted(set(items))

        for item in unique_items:
            print(f"{item} {items.count(item)}")

    # Creates a file with item frequencies for the bar chart
    def create_histogram_file(self, output_file='frequency.dat'):
        items = self._read_items()
        unique_items = sorted(set(items))

        with open(output_file, 'w') as file:
            for item in unique_items:
                file.write(f"{item} {items.count(item)}\n")


# These are required for C++ to call specific functions directly
# C++ can only call functions, not class methods, so we wrap them

# Prints all item quantities (used by C++)
def all_item_quantities():
    analyzer = GroceryAnalyzer()
    analyzer.all_item_quantities()

# Returns specific item quantity (used by C++)
def specific_item_quantity(v):
    analyzer = GroceryAnalyzer()
    return analyzer.specific_item_quantity(v)

# Creates the frequency.dat file (used by C++)
def read_and_create_file():
    analyzer = GroceryAnalyzer()
    analyzer.create_histogram_file()
