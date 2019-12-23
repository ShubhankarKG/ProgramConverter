import fs from 'fs'
import Scanner from './Scanner'

class ProgramConverter {
    hadError = false

    runFile = params => {
        fs.readFile(params, 'utf-8', (err, data) => {
            if (err) process.exit(65)
            run(data)
        })
        if (hadError) process.exit(65)
    }

    runPrompt = () => {
        for (; ;) {
            console.log('>')
            run(prompt())
            hadError = false
        }
    }

    run = params => {
        const scanner = new Scanner(params)
        let tokens = scanner.scanTokens()
        tokens.forEach(element => {
            console.log(element)
        });
    }

    error = (line, message) => {
        report(line, "", message)
    }

    report = (line, where, message) => {
        console.error("[line " + line + " ] Error" + where + ": " + message)
        hadError = true
    }
}

if (process.argv.length > 1) {
    console.log('Usage: programConverter [script]')
    process.exit(64)
} else if (process.argv.length === 1) {
    const programConverter = new ProgramConverter()
    programConverter.runFile(process.argv[2])
} else {
    const programConverter = new ProgramConverter()
    programConverter.runPrompt()
}

export default ProgramConverter