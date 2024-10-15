from mot_processing import *
import re
class Main:
    def __init__(self):
        self.motObj = mot_processing()
        self.mot, self.length = self.motObj.readMot()
        # print(self.length)
        self.txt = []
        self.symbol = {}
        self.literal = []
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
        lit = open("literal.txt", "w")

        p = []
        for l in self.txt:
            str = ""
            temp = ""
            inc = 1
            if (len(l) == 1 and l[0] == "ltorg"):
                for key in self.literal:
                    lit.write("='{}' {}\n".format(key, self.lc - 1))
                    self.lc += 1
                self.literal = []
            elif (l[0] in ["start", "end", "origin"]):
                str = "( AD, {} ) ".format(l[0]) + " ".join(l[1:]) + "\n"
            elif (l[0] in self.mot.keys()):
                print(l[0])
                str = "( IS, " + "{}".format(self.mot[l[0]]) + ") " + " ".join(l[1:]) + "\n"
                # print(l[0])
                if (l[0] in self.length.keys()):
                    # print(inc)
                    inc = self.length[l[0]]
                temp = " ".join(l[1:])
            else:
                self.symbol[l[0]] = self.lc - 1
                if (l[1] in self.mot.keys()):
                    str += "IS, "
                    str += "{}".format(self.mot[l[1]]) + ") " + " ".join(l[2:]) + "\n"
                    if (l[1] in self.length.keys()):
                        # print(inc)
                        inc = self.length[l[1]]
                else:
                    str += "DL, {}".format(l[1]) + ") " + " ".join(l[2:]) + "\n"
                temp = " ".join(l[2:])


            f = temp.find("=")

            if (f != -1):
                temp = temp.replace("'", '"')
                l = re.findall('"([^"]*)"', temp)
                print(re.findall('"([^"]*)"', temp))
                self.literal += l

            p.append(str)
            self.lc += inc

        temp = []
        for key in self.symbol:
            temp.append("{} {}\n".format(key, self.symbol[key]))

        for key in self.literal:
            lit.write("='{}' {}\n".format(key, self.lc - 2))
            self.lc += 1

        out.writelines(temp)
        fin = open("process.txt", "w")
        fin.writelines(p)
        fin.close()
        out.close()
        lit.close()

if __name__ == '__main__':
    obj = Main()
