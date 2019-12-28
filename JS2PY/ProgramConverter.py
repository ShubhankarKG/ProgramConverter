class ProgramConverter:
    hadError = False
    def runFile(self, path):
        f = open(path, 'r')
        inp = ''
        for x in f:
            inp += x
        run(inp)
        if(hadError): sys.exit()