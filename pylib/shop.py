from dataclasses import dataclass


@dataclass
class Item:
    name: str
    price: float

    def __repr__(self):
        return f"{self.name} (${self.price})"


available_items = [
    Item(name="Western Digital", price=90),
    Item(name="Lacie", price=100),
    Item(name="Seagate", price=95),
]


def show_items():
    print("-- Item Available --")
    for item in available_items:
        print(item)


def place_order(drive_type, number_of_drives, is_ohio_resident):
    pass
