AI Prompting:

- persona: set roles for the AI. resul,ts in narrowing focus
- context: more context = less halluciantions
	- never assume the ai knows everything and has all the context
	- another trick to limit hallucinations is to tell the AI to fail if the prompt and the context are not enough for him to give you an answer. its better to have him fail than to intentionally fill in the gaps with whatever information HE feels would fit.
- format: how you want the result to look
	- instruct the LLM what its answer should look like
	- an even better and more consistent way to this is by giving it real-world examples (Few Shot)
- COT (Chain of Thought):
	- the old way off doing this was telling the LLM the step-by-step process it needs to follow in its thinking process before answering. This thinking process will be visible to you as well so you can monitor what it actually does befor forming its final answer
	- most AI models have already baked this feature in their LLMs 
