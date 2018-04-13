import xlrd
import time


def prodofx(prodofxx, prodlist):
    for iprodlist in prodlist:
        if prodofxx == iprodlist[0]:
            return iprodlist[1:]


def firstofx(firstofxx, first):
    for ifirst in first:
        if ifirst[0] == firstofxx:
            return ifirst[1:]


def dotindex(listprod):
    for ilistprod in range(len(listprod)):
        if listprod[ilistprod] == 'Dot':
            return ilistprod


def afterdot(idot):
    idotre = list()
    for iidot in idot:
        afterindex = dotindex(iidot[1])
        if afterindex != len(iidot[1]) - 1 and iidot[1][afterindex+1] not in idotre:
            idotre.append(iidot[1][afterindex+1])
    return idotre


def getpvtfirst(path):
    frawbook = (xlrd.open_workbook(path))
    fgrammar = frawbook.sheet_by_index(3)
    fproductionlist = list()
    for firows in range(fgrammar.nrows):
        frow = fgrammar.row_values(firows)
        ftmp = list()
        for iprod in frow:
            if len(ftmp) == 0:
                ftmp.append(iprod)
            else:
                if iprod == '':
                    ftmp.append([])
                else:
                    ftmp[-1].append(iprod)
        if len(ftmp[-1]) != 0:
            fproductionlist.append(ftmp)
            continue
        while len(ftmp[-1]) == 0:
            ftmp.pop()
            if ftmp not in fproductionlist:
                fproductionlist.append(ftmp)

    fvt = frawbook.sheet_by_index(2)
    fv = list()
    ft = list()
    for firows in fvt.row_values(0):
        if firows != '':
            fv.append(firows)
    for firows in fvt.row_values(1):
        ft.append(firows)

    for fit in ft:
        fproductionlist.append([fit, [fit]])

    fsheet5 = frawbook.sheet_by_index(5)
    ffirstx = list()
    for fisheet5 in range(fsheet5.nrows):
        fs5row = fsheet5.row_values(fisheet5)
        while fs5row[-1] == '':
            fs5row.pop()
        ffirstx.append(fs5row)

    return fproductionlist, fv, ft, ffirstx


def getclosure(closurei):
    fi0 = closurei
    fleni0 = len(fi0)
    while True:
        for ifi0 in fi0:
            fdotindex = dotindex(ifi0[1])
            if fdotindex == len(ifi0[1])-1:
                continue
            tmpb = ifi0[1][fdotindex+1]
            if tmpb in T:
                continue
            if fdotindex == len(ifi0[1])-2:
                tmpbeta = 'Empty'
            else:
                tmpbeta = ifi0[1][fdotindex+2:]
            bprod = prodofx(tmpb, ProductionList)
            for ibprod in bprod:
                ftmpy = list(['Dot'])
                for ibprodmain in ibprod:
                    ftmpy.append(ibprodmain)
                if tmpbeta == 'Empty':
                    if ifi0[2] == '$':
                        if [tmpb, ftmpy, '$'] not in fi0:
                            fi0.append([tmpb, ftmpy, '$'])
                            continue
                    else:
                        for ifirstbetaa in firstofx(ifi0[2], FirstX):
                            if [tmpb, ftmpy, ifirstbetaa] not in fi0:
                                fi0.append([tmpb, ftmpy, ifirstbetaa])
                else:
                    notemptyfirst = firstofx(tmpbeta[0], FirstX)
                    for inotempty in notemptyfirst:
                        if [tmpb, ftmpy, inotempty] not in fi0:
                            fi0.append([tmpb, ftmpy, inotempty])
        fleni1 = len(fi0)
        if fleni1 == fleni0:
            break
        fleni0 = fleni1
    return sorted(fi0)


def goto(gotoi, gotox):
    gotoj = list()
    for igotoi in gotoi:
        gotodotindex = dotindex(igotoi[1])
        if gotodotindex == len(igotoi[1]) - 1:
            continue
        gototmpx = igotoi[1][gotodotindex+1]
        gototmpappend = []
        for iigoti in range(len(igotoi[1])):
            if iigoti == gotodotindex:
                gototmpappend.append(gototmpx)
            elif iigoti == gotodotindex+1:
                gototmpappend.append('Dot')
            else:
                gototmpappend.append(igotoi[1][iigoti])
        if gototmpx == gotox:
            gotoj.append([igotoi[0], gototmpappend, igotoi[2]])
    return getclosure(gotoj)


def getitems(items):
    itemslen0 = len(items)
    while True:
        for iitems in items:
            if len(items) == 1572:
                return items
            print(len(items))
            for ipl0 in afterdot(iitems):
                tmpitem = goto(iitems, ipl0)
                if tmpitem not in items and len(tmpitem) != 0:
                    items.append(tmpitem)
        itemslen1 = len(items)
        if itemslen1 == itemslen0:
            break
        itemslen0 = itemslen1
    return items


# def outc(items):


if __name__ == "__main__":
    time1 = time.time()
    rawpath = "/Users/wave/Downloads/Course/Compiler_Principle/Compiler/Grammar.xlsx"
    ProductionList, V, T, FirstX = getpvtfirst(rawpath)
    I0 = getclosure([['translation_unit!', ['Dot', 'translation_unit'], '$']])
    C = getitems([I0])
    time2 = time.time()
    print(time2-time1)
