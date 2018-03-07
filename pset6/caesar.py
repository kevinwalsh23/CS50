import cs50
import sys

z = 65
y = 97

def main():
    
    if len(sys.argv) != 2:
        print(" Usage: ./caesars k")
        return 1
    
    else:
        print("plaintext: ", end="")
        s = cs50.get_string()
        k = int(sys.argv[1])
    
        print("ciphertext: ", end="")
        
        for c in s:
            if ord(c) >= 65 and ord(c) <= 90:
                print("{}".format(chr((((ord(c)) + k - z) % 26) + z)), end="")
            
            elif ord(c) >= 97 and ord(c) <= 122:
                print("{}".format(chr((((ord(c)) + k - y) % 26) + y)), end="")
            
            else:
                j = c
                print("{}".format(j))
        
    print("")

if __name__ == "__main__":
    main()