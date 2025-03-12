This repo is the result of a thought exercise that I did over ten years ago in conjunction with all the so called “AI Thought Leaders" noise around junior and mid-level programmers being replaced by Generative AI by the end of 2025.  My conclusion is that some of the thought leaders might want to, in the words of Adam Grant, “Think Again”.  
The goal of the exercise is to see how well multiple foundational models can convert a simple Jupyter notebook / Python code to a handful of other languages. This is an all-day everyday occurrence that goes on in corporations across the globe where a simple prototype in one language is converted to language and is one that a junior or mid-level programmer could handle. 
This code is relatively simple in that it mimics the beat the streak game that a donut chain and now professional baseball sponsor. It is not a true simulation, but close enough to get the general flavor and gist.  Essentially the goal of the game is to pick enough games in a row where a member of your team gets a hit.  Pick enough games correctly, 57, and you beat Joe DiMaggio’s 56 game streak in 1941. 
There are a few variables represented in the simulation that require a bit of clarification. You can double down represented by the ‘multi-game’ variable or you can just pick one player per day. I left this at 1.25 meaning the simulation picks multiple players a quarter of the time.  The streak multiplier is at 2.0 meaning that if you are in a streak, you are twice as likely to get a hit in a game above and beyond your current batting average.  So for example the AL batting champ has .332 batting average with this multiplier assuming they are twice as likely to get a hit while they are streaking their average bumps up to .664.  The last notable variable is the max tries, so the code runs 10M simulations or 10M seasons to see if the streak can be beat. Other than that, the variables are self-explanatory. 
I tried to keep the Python libraries to simple ones as to not have the foundational models inventing their own, so only numpy and time.  This also made the conversion a bit easier for the model. The languages that I used for testing were Python, Java, C++, C, C#, and Rust, so your common resume driven development languages.  I tried a couple different paths of going from Python to the other languages and the foundational LLM models struggled a bit. Java was the hardest to cajole into getting a working version quickly. The easiest path was to convert to C++ from Python first and then go to the other languages from there. Also,  the LLMs did a decent job of getting this to run straight away in C++.  That said, they didn’t offer any basic software engineering enhancements and didn’t suggest any performance related enhancements for any of the languages tested even though the IDEs did provide some hints and tips on ways to optimize code and improve performance. 
For sake of comparison here are the runtime results for 10M seasons simulated. 

Language	Time	Longest Streak

Python (Anaconda) – Jupyter Notebook	23.85 seconds	with longest streak of 39

Python (PyCharm)	21.83 seconds	with longest streak of 43

Rust (RustRover)	14.97 seconds	with longest streak of 41

C (CLion)	0.78 seconds	with longest streak of 46

C++ (CLion)	0.67 seconds	with longest streak of 37

Java (IntelliJ)	0.72 seconds	with longest streak of 42

C#  (MS Visual Studio)	1.0 seconds	4with longest streak of4

I have a biased, but open-minded perspective. My conclusion is that for a simple task of moving code from one language to another, the LLMs can do the work of a junior programmer. But if you are asking the model to come up with the simulation in the first place and ask it on ways to make it better, then my money is on the junior programmers still versus the LLM. I think there a modest improvements that can be made, but when it comes to novel situations, even junior programmers, which most of us are in one or multiple languages still can make a simple conversion such as this much better than an LLM. 
