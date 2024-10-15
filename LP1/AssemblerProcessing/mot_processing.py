class mot_processing:
    def __init__(self):
        self.mot = {}

    def process(self):
        file = open("MOT.txt", 'r')

        for l in file:
            [key, val] = l.split(" ")
            self.mot[key.lower()] = val.strip().lower()
        return

    def readMot(self):
        self.process()
        return self.mot