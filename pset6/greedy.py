import cs50
import sys

def main():
    
    p=0
    n=0
    q=0
    d=0
    
    print("O hai! How much change is owed? ",end="")
    change = cs50.get_float()
    
    while change < 0.00:
        print("Retry, how much change",end="")
        change = cs50.get_float()
        if change > 0.00:
            break
    
    if change >= 0.00:
        x = change * 1000
    
    while x>= 250:
        x = x -250
        q += 1
    
    while x >= 100:
        x = x - 100
        d += 1
    
    while x >= 50:
        x = x - 50
        n += 1
    
    while x >= 10:
        x = x - 10
        p += 1
    
    total = p + n + d + q

    print("{}".format(total))

if __name__ == "__main__":
    main()