import { calculateInvestmentResults, formatter } from "../util/investment";

export default function Results({ userInput }) {
	const resultData = calculateInvestmentResults(userInput);
	return (
		<table id="result">
			<thead>
				<tr>
					<th>Year</th>
					<th>Investment Value</th>
					<th>Interest (Year)</th>
					<th>Total Interest</th>
					<th>Invested Capital</th>
				</tr>
			</thead>
			<tbody>
				{resultData.map((yearData) => {
					const initialInvestment =
						resultData[0].valueEndOfYear -
						resultData[0].interest -
						resultData[0].annualInvestment;
					const totalInterest =
						yearData.valueEndOfYear -
						yearData.annualInvestment * yearData.year -
						initialInvestment;
					const totalAmountInvested = yearData.valueEndOfYear - totalInterest;
					return (
						<tr key={yearData}>
							<td>{yearData.year}</td>
							<td>{formatter.format(yearData.valueEndOfYear)}</td>
							<td>{formatter.format(yearData.interestYear)}</td>
							<td>{formatter.format(totalInterest)}</td>
							<td>{formatter.format(totalAmountInvested)}</td>
						</tr>
					);
				})}
			</tbody>
		</table>
	);
}
