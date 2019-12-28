import fs from 'fs'
import { scanTokens } from './Scanner.mjs'

let hadError = false

const runFile = params => {
    fs.readFile(params, 'utf-8', (err, data) => {
        if (err) process.exit(65)
        run(data)
    })
    if (hadError) process.exit(65)
}

const runPrompt = () => {
    for (; ;) {
        console.log('>')
        process.stdin.resume();
        process.stdin.setEncoding("utf-8");
        let stdin_input = "";
        process.stdin.on("data", function (input) {
            stdin_input = input;
        });
        process.stdin.on("end", function () {
            run(stdin_input);
        });
        hadError = false
    }
}

const run = params => {
    let tokens = scanTokens(params)
    tokens.forEach(element => {
        console.log(element)
    });
}

export const error = (line, message) => {
    report(line, "", message)
}

const report = (line, where, message) => {
    console.error("[line " + line + " ] Error" + where + ": " + message)
    hadError = true
}

if (process.argv.length > 3) {
    console.log('Usage: programConverter [script]')
    process.exit(64)
} else if (process.argv.length === 3) {
    runFile(process.argv[2])
} else {
    runPrompt()
}
