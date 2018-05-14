from queue import Queue

class Node(object):
    def __init__(self):
        self.cnt=0
        self.next={}
        self.fail=None
        self.code=None

class ACMachina(object):
    def __init__(self):
        self.root = Node()
    def insert(self,word,code):
        now = self.root
        for i in word:
            if now.next.get( i )==None:
                now.next[i]=Node()
            now = now.next[i]
        now.cnt = 1
        now.code = code
    def search(self,word):
        now = self.root
        for i in word:
            if now.next.get(i) == None:
                return False
            now = now.next[i]
        if now.cnt>0:
            return True
        return False
    def ac_build(self):
        Q = Queue()
        self.root.fail = None
        Q.put(self.root)
        while Q.empty()==False :
            now = Q.get()
            for i in now.next:
                p = now.fail
                while p :
                    if p.next.get(i):
                        now.next[i].fail=p.next[i]
                        break
                    p = p.fail
                if p == None:
                    now.next[i].fail=self.root
                Q.put(now.next[i])
    def ac_search(self,target):
        now = self.root
        for i in range(len(target)):
            while now.next.get( target[i] ) == None and now!= self.root:
                now=now.fail
            if now.next.get(target[i])==None:
                now = self.root
            else:
                now = now.next[ target[i] ]
            p = now
            while p:
                if p.cnt!=0 :
                    print('pos:%d,match_code:%d' % (i,p.code) )
                p = p.fail


if __name__ == "__main__":
    ma = ACMachina()
    ma.insert("abc",1)
    ma.insert("abd",2)
    ma.ac_build()
    ma.ac_search('xxxabdcabdsddd')