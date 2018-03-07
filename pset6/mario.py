import cs50

def main():
    print("Height: ", end=' ')
    x = cs50.get_int()
    
    while x<0 or x>23:
        print("Height: ", end=' ')
        x = cs50.get_int()
        if x>0 and x<23:
            break
    
    for i in range(x):
        yell((x - i) - 1) 
        cough(i + 1)
        print("  ", end="")
        cough(i + 1)
        jell((x - i) - 1)
        print("")
        
   # print ("")
   
def yell(n):
        for i in range (n):
            print(" ",end="")
    
def cough(n):
        for i in range (n):
            print("#",end="")

def jell(n):
       for i in range (n):
          print(" ",end="")
        
    
if __name__ == "__main__":
    main()
    