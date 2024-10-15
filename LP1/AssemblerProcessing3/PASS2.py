
class Main:
    def __init__(self):
        self.lc = -1
        self.reg = {}
        self.regVal = 0
        self.symT = self.fetchSym()
        self.litT = self.fetchLit()
        print(self.litT)
        self.process()


        return

    def fetchLit(self):
        st = open("./literal.txt")
        d = {}
        for l in st:
            l = l.strip()
            l = l.split(" ")
            d[l[0]] = int(l[1])
        print(d)
        return d
    def fetchSym(self):
        st = open("./symbol.txt")
        d = {}
        for l in st:
            l = l.strip()
            l = l.split(" ")
            d[l[0]] = int(l[1])
        print(d)
        return d

    def process(self):
        f = open("process.txt")
        out = open("pass2op.txt", "w")

        for l in f:
            l = l.strip()
            l = l.strip("(")
            l = l.split(")")
            first = [x.strip() for x in l[0].split(",")]
            second = [x.strip() for x in l[1].split(",")]
            if (first[0] == "AD"):
                if (first[1] == "start"):
                    self.lc = int(second[0])
                continue

            str = "{}".format(self.lc)

            if (first[0] == "DL"):
                if (first[1] == "dc"):
                    str += " {}".format(second[0])
            else:
                str += " {}".format(first[1])

                for it in second:
                    if (it.endswith("reg")):
                        if (it not in self.reg.keys()):
                            self.reg[it] = self.regVal
                            self.regVal += 1
                        str += " {}".format(self.reg[it])
                    elif (it in self.symT.keys()):
                        str += " {}".format(self.symT[it])
                    elif (it in self.litT.keys()):
                        str += " {}".format(self.litT[it])
            self.lc += 1
            out.write(str + "\n")
            while (self.lc in self.litT.values()):
                x = ""
                for it in self.litT:
                    if (self.litT[it] == self.lc):
                        x = it
                        break
                out.write("{} {} \n".format(self.lc, x))
                self.lc += 1
            print(str)

            print(first, second)

        out.write("{}".format(self.lc))

if __name__ == '__main__':
    obj = Main()
