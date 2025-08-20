import json, os

userfile = "list.json"

def main():
    print("Enter To-do List")
    
    # If file exists, load existing items, else start fresh
    if os.path.exists(userfile):
        try:
            with open(userfile, "r") as f:
                todo_list = json.load(f)
        except (json.JSONDecodeError, IOError):
            todo_list = []
    else:
        todo_list = []

    i = len(todo_list) + 1  # Continue numbering
    
    while True:
        item = input(f"{i}. Name: ")
        todo_list.append(item)
        ans = input("Do you wanna Add more? : ").lower().strip()
        if ans in ("y", "yes"):
            i += 1
            continue
        else:
            break

    try:
        with open(userfile, "w") as f:
            json.dump(todo_list, f, indent=4)
    except (TypeError, IOError) as e:
        print("Error in coding:", e)

if __name__ == "__main__":
    main()
