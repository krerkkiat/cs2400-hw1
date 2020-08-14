from dataclasses import dataclass

OHIO_TAX_RATE = 0.07


@dataclass
class Item:
    name: str
    price: float
    discount: float

    def __repr__(self):
        return f"{self.name} (${self.price})"


available_items = [
    Item(name="Western Digital", price=90, discount=0.05),
    Item(name="Lacie", price=100, discount=0.03),
    Item(name="Seagate", price=95, discount=0.10),
]


def show_items():
    print("-- Item Available --")
    for item in available_items:
        print(item)


def get_drive_name():
    choices = ["W", "S", "L"]


def place_order(drive_name, number_of_drives, is_ohio_resident):
    item = None
    if drive_name == "W":
        item = available_items[0]
    elif drive_name == "L":
        item = available_items[1]
    elif drive_name == "S":
        item = available_items[2]

    total_price = item.price * number_of_drives
    discount = total_price * item.discount
    sub_total = total_price - discount

    print("\n\n-- Hard Drives Order --")
    print(f"Drive brand: {item.name}")
    print(f"Quantity: {number_of_drives}")

    if is_ohio_resident == 1:
        print("Ohio Resident: Yes")
    else:
        print("Ohio Resident: No")

    print(f"\nTotal price: ${total_price:0.2f}")
    print("---------------------------\n")

    print(f"Discount: -${discount}")
    print(f"Subtotal: ${sub_total}")

    ohio_taxes = 0.0

    if is_ohio_resident:
        ohio_taxes = sub_total * OHIO_TAX_RATE
        print(f"Ohio Taxes: ${ohio_taxes}")
    else:
        print(f"Ohio Taxes: ${ohio_taxes}")
    print("============================\n")
    total = sub_total + ohio_taxes
    print(f"Total: ${total}\n\n")

