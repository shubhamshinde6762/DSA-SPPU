class mot_processing:
    def __init__(self):
        self.mot = {}
        self.lc = {}

    def process(self):
        file = open("MOT.txt", 'r')

        for l in file:
            l = l.strip()
            l = l.split(" ")
            self.mot[l[0].lower()] = l[1].strip().lower()
            if (len(l) >= 3):
                self.lc[l[0].lower()] = int(l[2])
                # print(int(l[2]))
        return

    def readMot(self):
        self.process()
        return self.mot, self.lc