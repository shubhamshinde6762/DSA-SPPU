import ast
class Pass2:

    def __init__(self):
        self.mnt = {}
        self.mdt = {}
        self.plt = {}
        self.op = []
        self.index = 1
        return

    def process(self):
        op = open("/home/pict/Documents/31484/macro/utils/output/op")
        mdt = open("/home/pict/Documents/31484/macro/utils/output/mdt")
        mnt = open("/home/pict/Documents/31484/macro/utils/output/mnt")
        plt = open("/home/pict/Documents/31484/macro/utils/output/plt")
        pass2 = open("/home/pict/Documents/31484/macro/utils/output/pass2", "w")

        for l in mdt:
            l = l.split()
            self.mdt[int(l[0])] = " ".join(l[1:])

        for l in mnt:
            l = l.split()
            self.mnt[l[0]] = int(l[1])

        for l in plt:
            l = l.split()
            self.plt[l[0]] = ast.literal_eval(" ".join(l[1:]))
        print(self.plt)


        for l in op:
            l = l.split()
            print(l[0])
            if l[0] not in self.mnt.keys():
                pass2.write(" ".join(l) + "\n")
                continue

            opstr = ""
            start = self.mnt[l[0]]

            while(True):
                if (self.mdt[start] == "mend"):
                    break

                opstr += self.mdt[start] + " \n"
                start += 1

            par = {}
            q = self.plt[l[0]]

            flag = True
            # print("l", l)
            for i in range(1, len(q)):
                # print(q[i], i)
                if i < len(l):
                    q[i] = q[i].split('=')[0]
                    # print(q[i])
                    par[q[i]] = l[i]
                elif ('=' in q[i]):
                    par[q[i].split('=')[0]] = q[i].split('=')[1]
                else:
                    print("error")
                    return


            print(opstr)
            for key in par.keys():
                print(key, par[key])
                opstr = opstr.replace(key, par[key])
            print(opstr)

            pass2.write(opstr)
