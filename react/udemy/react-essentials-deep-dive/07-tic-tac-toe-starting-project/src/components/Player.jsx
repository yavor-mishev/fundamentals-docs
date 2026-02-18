import { useState } from "react";

export default function Player({ name, symbol, isActive }) {
	const [playerName, setPlayerName] = useState(name);
	const [isEditing, setIsEditing] = useState(false);

	function handleClick() {
		setIsEditing((editing) => !editing);
	}

	function handleChange(event) {
		setPlayerName(event.target.value);
	}
	return (
		<li className={isActive ? "active" : undefined}>
			<span className="player">
				{!isEditing ? (
					<span className="player-name">{playerName}</span>
				) : (
					<input value={playerName} onChange={handleChange} />
				)}
				<span className="player-symbol">{symbol}</span>
			</span>
			<button onClick={handleClick}>{isEditing ? "Save" : "Edit"}</button>
		</li>
	);
}
