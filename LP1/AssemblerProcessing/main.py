from mot_processing import *
class Main:
    def __init__(self):
        self.motObj = mot_processing()
        self.mot = self.motObj.readMot()
        self.txt = []
        self.symbol = {}
        self.lc = -1
        self.fetchTxt()
        self.process()
        return

    def fetchTxt(self):
        pro = open("programe.txt")
        for l in pro:
            self.txt.append(l.strip().lower().split(' '))
        if (len(self.txt[0]) == 2 and self.txt[0][0] != 'start'):
            print('Wrong data')
        self.lc = int(self.txt[0][1])
        print(self.txt)

    def process(self):
        out = open("symbol.txt", "w")

        p = []
        for l in self.txt:
            str = "("
            if (l[0] in self.mot.keys()):
                if (l[0] in ["start", "end"]):
                    str += "AD, "
                else:
                    str += "IS, "
                str += "{}".format(self.mot[l[0]]) + ") " + " ".join(l[1:]) + "\n"
            else:
                self.symbol[l[0]] = self.lc - 1
                if (l[1] in self.mot.keys()):
                    str += "IS, "
                    str += "{}".format(self.mot[l[1]]) + ") " + " ".join(l[2:]) + "\n"
                else:
                    str += "DL, {}".format(l[1]) + ") " + " ".join(l[2:]) + "\n"


            p.append(str)
            self.lc += 1

        temp = []
        for key in self.symbol:
            temp.append("{} {}\n".format(key, self.symbol[key]))

        out.writelines(temp)

        fin = open("process.txt", "w")
        fin.writelines(p)

if __name__ == '__main__':
    obj = Main()
