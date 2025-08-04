function toUsd(aNumber) {
    return new Intl.NumberFormat('en-US', {
        style: 'currency',
        currency: 'USD',
        minimumFractionDigits: 2,
    }).format(aNumber / 100);
}

export function statement(aInvoice, plays) {
    let totalAmount = 0;
    let volumeCredits = 0;
    let result = `Statement for ${aInvoice.customer}\n`;
    for (let aPerformance of aInvoice.performances) {
        let thisAmount = getAmountFor(aPerformance);
        // print line for this order
        result += `  ${getPlayFor(aPerformance).name}: ${toUsd(thisAmount)} (${
            aPerformance.audience
        } seats)\n`;
        totalAmount += thisAmount;
    }
    for (let aPerformance of aInvoice.performances) {
        volumeCredits += getVolumeCreditsFor(aPerformance);
    }
    result += `Amount owed is ${toUsd(totalAmount)}\n`;
    result += `You earned ${volumeCredits} credits\n`;
    return result;

    function getAmountFor(aPerformance) {
        let result = 0;
        switch (getPlayFor(aPerformance).type) {
            case 'tragedy':
                result = 40000;
                if (aPerformance.audience > 30) {
                    result += 1000 * (aPerformance.audience - 30);
                }
                break;
            case 'comedy':
                result = 30000;
                if (aPerformance.audience > 20) {
                    result += 10000 + 500 * (aPerformance.audience - 20);
                }
                result += 300 * aPerformance.audience;
                break;
            default:
                throw new Error(
                    `unknown type: ${getPlayFor(aPerformance).type}`
                );
        }
        return result;
    }

    function getPlayFor(aPerformance) {
        return plays[aPerformance.playID];
    }

    function getVolumeCreditsFor(aPerformance) {
        let result = Math.max(aPerformance.audience - 30, 0);
        if ('comedy' === getPlayFor(aPerformance).type)
            result += Math.floor(aPerformance.audience / 5);
        return result;
    }
}
