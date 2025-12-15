def pyramid():

    while True:
        user_input = input("Height: ")
        try:
            height = int(user_input) 
            
            if 0 < height <= 8:
                for blocks in range(height):
                    print(" " * (height-(blocks + 1)), end="")
                    print("#" * (blocks + 1), end="")
                    print("  ", end="")
                    print("#" * (blocks + 1))
                return
    
        except ValueError:
            continue


pyramid()
