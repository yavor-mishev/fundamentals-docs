import { useState } from "react";

const initialGameBoard = [
	[null, null, null],
	[null, null, null],
	[null, null, null],
];

export default function GameBoard({ onSelectSquare, activePlayerSymbol }) {
	const [gameBoard, setGameBoard] = useState(initialGameBoard);

	function handleSelectSquared(rowIndex, colIndex) {
		setGameBoard((prevGameBoard) => {
			const updatedGameBoard = [
				...prevGameBoard.map((innerArr) => [...innerArr]),
			];
			updatedGameBoard[rowIndex][colIndex] = activePlayerSymbol;
			return updatedGameBoard;
		});
		onSelectSquare();
	}
	return (
		<ol id="game-board">
			{gameBoard.map((row, rowIndex) => (
				<li key={rowIndex}>
					<ol>
						{row.map((playerSymbol, colIndex) => (
							<li key={colIndex}>
								<button onClick={() => handleSelectSquared(rowIndex, colIndex)}>
									{playerSymbol}
								</button>
							</li>
						))}
					</ol>
				</li>
			))}
		</ol>
	);
}
