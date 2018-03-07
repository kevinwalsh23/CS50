import nltk
from nltk.tokenize import TweetTokenizer

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        #self.positives = set()
        
        self.positives = set()
        pos_file = open(positives, "r")
        for line in pos_file:
            if line.startswith(';'):
                x = 1
            else:
               #print(line.rstrip(" "))
               self.positives.add(line.rstrip('\n'))
        pos_file.close()
        #print(self.positives)
        
        self.negatives = set()
        neg_file = open(negatives, "r")
        for line in neg_file:
            if line.startswith(';'):
                x = 1
            else:
              # print(line.rstrip(" "))
               self.negatives.add(line.rstrip("\n"))
                
        neg_file.close()
        
         # TODO

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        # TODO
        
        a = 0
        b = 0
        #d = 0
        #tknzr = TweetTokenizer(strip_handles=True, reduce_len=True)
        tknzr = TweetTokenizer()
        tokens = tknzr.tokenize(text)
        for k in tokens:
            #print(k)
            if k.lower() in self.positives:
                a += 1
            elif k.lower() in self.negatives:
                b -= 1
        
        score = a + b
        return score
            
            
