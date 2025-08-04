import fs from 'node:fs';
import path from 'node:path';
import * as url from 'url';

import { statement as before_statement } from './before';
import { statement as after_statement } from './after';

const __dirname = url.fileURLToPath(new URL('.', import.meta.url));

const output = `Statement for BigCo
  Hamlet: $650.00 (55 seats)
  As You Like It: $580.00 (35 seats)
  Othello: $500.00 (40 seats)
Amount owed is $1,730.00
You earned 47 credits\n`;

test('after matches before', () => {
    const plays_str = fs.readFileSync(path.join(__dirname, './plays.json'), {
        encoding: 'utf-8',
    });
    let plays;
    try {
        plays = JSON.parse(plays_str);
    } catch (error) {
        console.error(error);
        return;
    }

    const invoices_str = fs.readFileSync(
        path.join(__dirname, './invoices.json'),
        {
            encoding: 'utf-8',
        }
    );
    let invoices;
    try {
        invoices = JSON.parse(invoices_str);
    } catch (error) {
        console.error(error);
        return;
    }

    const expected = before_statement(invoices[0], plays);
    expect(expected).toEqual(output);
    const actual = after_statement(invoices[0], plays);
    expect(actual).toEqual(output);
});
