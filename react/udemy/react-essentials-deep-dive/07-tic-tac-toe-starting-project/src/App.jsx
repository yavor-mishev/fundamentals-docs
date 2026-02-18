import { useState } from "react";

import Player from "./components/Player";
import GameBoard from "./components/GameBoard";
import Log from "./components/Log";
import { use } from "react";

function App() {
	const [activePlayer, setActivePlayer] = useState("X");

	function handleSelectSquare() {
		setActivePlayer((curr) => (curr === "X" ? "O" : "X"));
	}
	return (
		<main>
			<div id="game-container">
				<ol id="players" className="highlight-player">
					<Player name="Player 1" symbol="X" isActive={activePlayer === "X"} />
					<Player name="Player 2" symbol="O" isActive={activePlayer === "O"} />
				</ol>
				<GameBoard
					onSelectSquare={handleSelectSquare}
					activePlayerSymbol={activePlayer}
				/>
			</div>
			<Log></Log>
		</main>
	);
}

export default App;
