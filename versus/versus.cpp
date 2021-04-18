#include<bangtal.h>
#include<cstdlib>
#include<ctime>
#include <string>


SceneID startScreen, gameScreen, gameOver;

ObjectID title;
ObjectID player, enemy, playerEff, enemyEff, bang, frameEff;
ObjectID startButton, infinityButton, helpButton, screenClicker;
ObjectID fadeImage, blackScreen;
ObjectID dial, dialChar;

TimerID waitTimer, attackTimer, plEffTimer, enEffTimer, effEndTimer, fadeTimer, downTimer, nextTimer, endTimer, overTimer;

SoundID piano, tension, bangSound, atkSound, downSound, buttonSound;


bool canAttack = false;
bool isMatchStarted = false;
bool cleared = false;
bool infinity = false;

int plEffNum = -1;
int enemyNum = 1;
int fadeNum = 0;
int nextScene = 0;
int dialNum = 1;
int enEffNum = 0;
int enEffType = 1;
int score = 0;

float speed = 0.45f;


void prep() {
	showObject(frameEff);
	playSound(piano);
	playSound(tension);
	setTimer(waitTimer, 5 + (rand() % 20 + 1) * 0.1f);
	startTimer(waitTimer);
	showObject(screenClicker);
}


void diallog(int character) {

	std::string dialStr = "dial/dial_" + std::to_string(dialNum) + ".png";
	const char* dialFile = dialStr.c_str();
	setObjectImage(dial, dialFile);

	
	if (character == 0) {
		locateObject(dialChar, gameScreen, 200, 100);
		setObjectImage(dialChar, "Char/char.png");
		showObject(dialChar);
	}
	else if (character <= 5) {
		locateObject(dialChar, gameScreen, 730, 100);
		std::string charStr = "Char/enemy_" + std::to_string(character) + ".png";
		const char* charFile = charStr.c_str();
		setObjectImage(dialChar, charFile);
		showObject(dialChar);
	}
	else if (character == 6) {

		locateObject(dialChar, gameScreen, 200, 100);
		setObjectImage(dialChar, "Char/enemy_6.png");
		showObject(dialChar);

	}
	locateObject(screenClicker, gameScreen, 0, 0);
	showObject(dialChar);
	showObject(dial);
	showObject(screenClicker);
	if (character == -1) {
		hideObject(dialChar);
	}
	dialNum++;

}


void fadeScene() {

	if (fadeNum < 12) {
		std::string fadeStr = "BG/fade" + std::to_string(fadeNum) + ".png";
		const char* fadeFile = fadeStr.c_str();

		setObjectImage(fadeImage, fadeFile);
		setTimer(fadeTimer, 0.07f);
		startTimer(fadeTimer);

		fadeNum++;

		if (fadeNum == 8) {
			if (nextScene == 1)
			{
				std::string enemyStr = "Char/enemy_" + std::to_string(enemyNum) + ".png";
				const char* enemyFile = enemyStr.c_str();
				setObjectImage(enemy, enemyFile);
				locateObject(fadeImage, gameScreen, 0, 0);
				enterScene(gameScreen);
				diallog(0);
			}
			if (nextScene == 2) {
				prep();
			}
			if (nextScene == 3) {
				locateObject(player, gameScreen, 330, 150);
				locateObject(enemy, gameScreen, 830, 150);
				hideObject(enemy);
				if (enemyNum == 5) {
					setSceneImage(gameScreen, "BG/night.jpg");
				}
				std::string enemyStr = "Char/enemy_" + std::to_string(enemyNum) + ".png";
				const char* enemyFile = enemyStr.c_str();
				setObjectImage(enemy, enemyFile);
			}
			if (nextScene == 4)
			{
				setSceneImage(gameScreen, "BG/noon.jpg");
				locateObject(fadeImage, startScreen, 0, 0);
				enterScene(startScreen);
			}
			if (nextScene == 5)
			{
				std::string enemyStr = "Char/enemy_" + std::to_string(rand()%14+8) + ".png";
				const char* enemyFile = enemyStr.c_str();
				setObjectImage(enemy, enemyFile);
				locateObject(fadeImage, gameScreen, 0, 0);
				enterScene(gameScreen);
				prep();
			}
			if (nextScene == 6)
			{
				setSceneImage(gameScreen, "BG/noon.jpg");
				hideObject(blackScreen);
				std::string enemyStr = "Char/enemy_" + std::to_string(rand() % 14 + 8) + ".png";
				const char* enemyFile = enemyStr.c_str();
				setObjectImage(enemy, enemyFile);
				prep();
			}

		}

		if (fadeNum == 12) {

			if (nextScene == 1){

			}
			if (nextScene == 2) {
				isMatchStarted = true;
				showObject(screenClicker);
			}
			if (nextScene == 3) {
				dialNum--;
				if (enemyNum == 3) {
					diallog(2);
				}
				else {
					diallog(0);
				}
			}
			if (nextScene == 5){
				isMatchStarted = true;
				showObject(screenClicker);
			}
			if (nextScene == 6) {
				isMatchStarted = true;
				showObject(screenClicker);
			}

			stopTimer(fadeTimer);
			hideObject(fadeImage);
			fadeNum = 0;
		}

	}
}

void enemyAtk1() {

	if (enEffNum <= 4) {
		std::string enEffStr = "Effect/enemyEff1_"  + std::to_string(enEffNum) + ".png";
		const char* enEffFile = enEffStr.c_str();
		setObjectImage(enemyEff, enEffFile);
		enEffNum++;
		setTimer(enEffTimer, 0.04f);
		startTimer(enEffTimer);
	}
	else if (enEffNum == 5) {
		hideObject(enemyEff);
		enEffNum = 0;
	}

}

void enemyAtk2() {

	if (enEffNum <= 14) {
		std::string enEffStr = "Effect/enemyEff2_" + std::to_string(enEffNum) + ".png";
		const char* enEffFile = enEffStr.c_str();
		setObjectImage(enemyEff, enEffFile);
		enEffNum++;
		setTimer(enEffTimer, 0.03f);
		startTimer(enEffTimer);
	}
	else{
		hideObject(enemyEff);
		enEffNum = 0;
	}

}

void enemyAtk3() {

	if (enEffNum <= 9) {
		std::string enEffStr = "Effect/enemyEff3_" + std::to_string(enEffNum) + ".png";
		const char* enEffFile = enEffStr.c_str();
		setObjectImage(enemyEff, enEffFile);
		enEffNum++;
		setTimer(enEffTimer, 0.03f);
		startTimer(enEffTimer);
	}
	else {
		hideObject(enemyEff);
		enEffNum = 0;
	}

}

void enemyAtk4() {

	if (enEffNum <= 10) {
		std::string enEffStr = "Effect/enemyEff4_" + std::to_string(enEffNum) + ".png";
		const char* enEffFile = enEffStr.c_str();
		setObjectImage(enemyEff, enEffFile);
		enEffNum++;
		setTimer(enEffTimer, 0.03f);
		startTimer(enEffTimer);
	}
	else if (enEffNum == 11) {
		hideObject(enemyEff);
		enEffNum = 0;
	}

}

void enemyAtk5() {

	if (enEffNum <= 8) {
		std::string enEffStr = "Effect/enemyEff5_" + std::to_string(enEffNum) + ".png";
		const char* enEffFile = enEffStr.c_str();
		setObjectImage(enemyEff, enEffFile);
		enEffNum++;
		setTimer(enEffTimer, 0.03f);
		startTimer(enEffTimer);
	}
	else if (enEffNum == 9) {
		hideObject(enemyEff);
		enEffNum = 0;
	}

}

void enemyAtk6() {

	if (enEffNum <= 19) {
		std::string enEffStr = "Effect/enemyEff6_" + std::to_string(enEffNum) + ".png";
		const char* enEffFile = enEffStr.c_str();
		setObjectImage(enemyEff, enEffFile);
		enEffNum++;
		setTimer(enEffTimer, 0.03f);
		startTimer(enEffTimer);
	}
	else if (enEffNum == 20) {
		hideObject(enemyEff);
		enEffNum = 0;
	}

}

void enemyAtk7() {

	if (enEffNum <= 14) {
		std::string enEffStr = "Effect/enemyEff7_" + std::to_string(enEffNum) + ".png";
		const char* enEffFile = enEffStr.c_str();
		setObjectImage(enemyEff, enEffFile);
		enEffNum++;
		setTimer(enEffTimer, 0.03f);
		startTimer(enEffTimer);
	}
	else if (enEffNum == 15) {
		hideObject(enemyEff);
		enEffNum = 0;
	}

}


void timerCallback(TimerID timer) {

	if (timer == plEffTimer) {

		if (plEffNum <= 8) {
			std::string plEffStr = "Effect/atkEff_" + std::to_string(plEffNum) + ".png";
			const char* plEffFile = plEffStr.c_str();
			setObjectImage(playerEff, plEffFile);
			plEffNum++;
			setTimer(timer, 0.05f);
			startTimer(timer);
		}
		else {
			stopTimer(plEffTimer);
			hideObject(playerEff);
			plEffNum = -1;
		}


	}

	if (timer == fadeTimer) {

		fadeScene();

	}

	if (timer == waitTimer) {
		canAttack = true;
		stopSound(tension);
		showObject(bang);
		playSound(bangSound);
		switch (enemyNum)
		{
		case 1:
			setTimer(attackTimer, 0.5f);
			break;
		case 2:
			setTimer(attackTimer, 0.42f);
			break;
		case 3:
			setTimer(attackTimer, 0.35f);
			break;
		case 4:
			setTimer(attackTimer, 0.3f);
			break;
		case 5:
			setTimer(attackTimer, 0.23f);
			break;
		case 6:
			setTimer(attackTimer, 0.23f);
			break;
		case 7:
			speed = speed * 0.95;
			setTimer(attackTimer, speed);
			break;
		}

		startTimer(attackTimer);
	}

	if (timer == downTimer) {
		if (enemyNum==5) {
			canAttack = true;
			showObject(bang);
			playSound(bangSound);
			enemyNum++;
		}
		else
		{
			if (enemyNum == 6) {
				enemyNum--;
			}
			std::string enemyStr = "Char/enemy_" + std::to_string(enemyNum) + "d.png";
			const char* enemyFile = enemyStr.c_str();
			setObjectImage(enemy, enemyFile);
			locateObject(enemy, gameScreen, 430, 90);
			playSound(downSound);
			enemyNum++;
			setTimer(nextTimer, 2.0f);
			startTimer(nextTimer);
		}
		
	}

	if (timer == nextTimer) {
		nextScene = 3;
		showObject(fadeImage);
		fadeScene();
	}

	if (timer == enEffTimer) {

		switch (enEffType)
		{
		case 1: enemyAtk1();
			break;
		case 2: enemyAtk2();
			break;
		case 3: enemyAtk3();
			break;
		case 4: enemyAtk4();
			break;
		case 5: enemyAtk5();
			break;
		case 6: enemyAtk6();
			break;
		case 7: enemyAtk7();
			break;
		}

	}

	if (timer == effEndTimer) {
		if (enemyNum==7)
		{
			fadeNum = 3;
			showObject(fadeImage);
			nextScene = 6;
			fadeScene();
		}
		else
		{
			hideObject(blackScreen);
			locateObject(player, gameScreen, 730, 150);
			locateObject(enemy, gameScreen, 430, 150);
			setTimer(downTimer, 2.5f);
			startTimer(downTimer);
			if (enemyNum == 5) {
				showObject(screenClicker);
			}
		}
		
	}

	if (timer == attackTimer&&canAttack) {
		showObject(blackScreen);
		if (enemyNum != 7) {
			showObject(enemyEff);
		}
		hideObject(bang);
		hideObject(frameEff);
		setTimer(endTimer, 2.5f);
		startTimer(endTimer);
		isMatchStarted = false;
		canAttack = false;
		switch (enemyNum)
		{
		case 1: enEffType = 1;
			locateObject(enemyEff, gameScreen, 350, 0);
			enemyAtk1();
			break;
		case 2: locateObject(enemyEff, gameScreen, 100, -100);
			enEffType = 2;
			enemyAtk2();
			break;
		case 3: enEffType = 3;
			locateObject(enemyEff, gameScreen, 200, -150);
			enemyAtk3();
			break;
		case 4: enEffType = 5;
			locateObject(enemyEff, gameScreen, 0, -150);
			enemyAtk5();
			break;
		case 5: enEffType = 6;
			enemyAtk6();
			break;
		case 6: enEffType = 7;
			enemyAtk7();
			break;
		}
	}
	if (timer == endTimer) {
		enterScene(gameOver);
		setTimer(overTimer, 2.0f);
		startTimer(overTimer);
		if (enemyNum == 7) {
			std::string scoreStr = "이번엔 " + std::to_string(score) + "명 쓰러뜨렸습니다!\n더 높은 기록을 노려봐요!";
			const char* scoreChar = scoreStr.c_str();
			showMessage(scoreChar);
		}
		
	}
	if (timer == overTimer) {
		dialNum = 1;
		enemyNum = 1;
		nextScene = 4;
		score = 0;
		speed = 0.45f;
		hideObject(blackScreen);
		showObject(fadeImage);
		fadeScene();
	}


}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == screenClicker) {

		if (canAttack && isMatchStarted && enemyNum < 5) {
			stopTimer(attackTimer);
			showObject(blackScreen);
			showObject(enemyEff);
			playSound(atkSound);
			plEffNum = 0;
			setTimer(plEffTimer, 0.05f);
			showObject(playerEff);
			startTimer(plEffTimer);
			canAttack = false;
			isMatchStarted = false;
			hideObject(bang);
			hideObject(frameEff);
			hideObject(screenClicker);
			setTimer(effEndTimer, 1.4f);
			startTimer(effEndTimer);
			switch (enemyNum)
			{
			case 1: enEffType = 1;
				locateObject(enemyEff, gameScreen, 350, 0);
				enemyAtk1();
				break;
			case 2: locateObject(enemyEff, gameScreen, 100, -100);
				enEffType = 2;
				enemyAtk2();
				break;
			case 3: enEffType = 3;
				locateObject(enemyEff, gameScreen, 200, -150);
				enemyAtk3();
				break;
			case 4: enEffType = 5;
				locateObject(enemyEff, gameScreen, 0, -150);
				enemyAtk5();
				break;
			case 5: enEffType = 6;
				enemyAtk6();
				break;
			}
		}

		else if (canAttack && isMatchStarted && enemyNum == 5) {
			stopTimer(attackTimer);
			showObject(blackScreen);
			showObject(enemyEff);
			playSound(atkSound);
			plEffNum = 0;
			setTimer(plEffTimer, 0.05f);
			showObject(playerEff);
			startTimer(plEffTimer);
			canAttack = false;
			hideObject(bang);
			hideObject(frameEff);
			setTimer(effEndTimer, 1.4f);
			startTimer(effEndTimer);
			enEffType = 6;
			enemyAtk6();
		}

		else if (canAttack && isMatchStarted && enemyNum == 6){
			stopTimer(attackTimer);
			showObject(blackScreen);
			playSound(atkSound);
			plEffNum = 0;
			setTimer(plEffTimer, 0.05f);
			showObject(playerEff);
			startTimer(plEffTimer);
			canAttack = false;
			isMatchStarted = false;
			hideObject(bang);
			hideObject(frameEff);
			hideObject(screenClicker);
			setTimer(effEndTimer, 1.4f);
			startTimer(effEndTimer);
			enEffType = 7;
			enemyAtk7();
		}

		else if (canAttack && isMatchStarted && enemyNum == 7) {
			stopTimer(attackTimer);
			showObject(blackScreen);
			playSound(atkSound);
			plEffNum = 0;
			setTimer(plEffTimer, 0.05f);
			showObject(playerEff);
			startTimer(plEffTimer);
			canAttack = false;
			isMatchStarted = false;
			hideObject(bang);
			hideObject(frameEff);
			hideObject(screenClicker);
			setTimer(effEndTimer, 1.0f);
			startTimer(effEndTimer);
			score++;
		}
		
		else if (isMatchStarted) {
			stopSound(tension);
			showObject(blackScreen);
			if (enemyNum != 7) {
				showObject(enemyEff);
			}
			hideObject(bang);
			hideObject(frameEff);
			stopTimer(waitTimer);
			setTimer(endTimer, 2.5f);
			startTimer(endTimer);
			isMatchStarted = false;
			canAttack = false;
			switch (enemyNum)
			{
			case 1: enEffType = 1;
				locateObject(enemyEff, gameScreen, 350, 0);
				enemyAtk1();
				break;
			case 2: locateObject(enemyEff, gameScreen, 100, -100);
				enEffType = 2;
				enemyAtk2();
				break;
			case 3: enEffType = 3;
				locateObject(enemyEff, gameScreen, 200, -150);
				enemyAtk3();
				break;
			case 4: enEffType = 5;
				locateObject(enemyEff, gameScreen, 0, -150);
				enemyAtk5();
				break;
			case 5: enEffType = 6;
				enemyAtk6();
				break;
			case 6: enEffType = 7;
				enemyAtk7();
				break;
			}
		}

		else {

			hideObject(screenClicker);
			hideObject(dial);
			hideObject(dialChar);

			switch (dialNum)
			{
			case 2: diallog(1);
				break;
			case 3: diallog(0);
				break;
			case 4:
				nextScene = 2;
				showObject(fadeImage);
				fadeScene();
				dialNum++;
				break;
			case 5: diallog(2);
				showObject(enemy);
				break;
			case 6: diallog(0);
				break;
			case 7:
				nextScene = 2;
				showObject(fadeImage);
				fadeScene();
				dialNum++;
				break;
			case 8: diallog(0);
				break;
			case 9: diallog(0);
				showObject(enemy);
				break;
			case 10: diallog(3);
				break;
			case 11: diallog(0);
				break;
			case 12:
				nextScene = 2;
				showObject(fadeImage);
				fadeScene();
				dialNum++;
				break;
			case 13: diallog(0);
				break;
			case 14: showObject(enemy);
				diallog(4);
				break;
			case 15: diallog(0);
				break;
			case 16: diallog(4);
				break;
			case 17:
				nextScene = 2;
				showObject(fadeImage);
				fadeScene();
				dialNum++;
				break;
			case 18: showObject(enemy); 
				diallog(5);
				break;
			case 19: diallog(0);
				break;
			case 20: diallog(5);
				break;
			case 21: diallog(0);
				break;
			case 22: diallog(5);
				break;
			case 23: diallog(5);
				break;
			case 24: diallog(0);
				break;
			case 25: diallog(5);
				break;
			case 26: diallog(0);
				break;
			case 27: nextScene = 2;
				showObject(fadeImage);
				fadeScene();
				dialNum++; 
				break;
			case 28: showObject(enemy); 
				diallog(5);
				break;
			case 29: diallog(0);
				break;
			case 30: diallog(6);
				break;
			case 31: diallog(5);
				break;
			case 32: diallog(5);
				break;
			case 33: diallog(0);
				break;
			case 34: diallog(-1);
				break;
			case 35: diallog(-1);
				break;
			case 36:
				dialNum = 1;
				enemyNum = 1;
				nextScene = 4;
				showObject(fadeImage);
				fadeScene();
				break;
			}
			
			
		}

	}

	if (object == startButton) {
		nextScene = 1;
		showObject(fadeImage);
		playSound(buttonSound);
		fadeScene();
	}
	if (object == helpButton) {
		playSound(buttonSound);
		showMessage("간단한 반응속도 게임입니다.\n\n!!표시가 나오면 화면 아무 곳을 재빠르게 클릭하세요!");
	}

	if (object == infinityButton) {
		playSound(buttonSound);
		enemyNum = 7;
		showObject(fadeImage);
		nextScene = 5;
		fadeScene();
	}

}




int main() {

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	
	startScreen = createScene("", "BG/start.jpg");
	gameScreen = createScene("", "BG/noon.jpg");
	gameOver = createScene("", "BG/gameOver.png");

	title = createObject("BG/title.png");
	locateObject(title, startScreen, 200, 100);
	scaleObject(title, 1.3);
	showObject(title);

	startButton = createObject("UI/normal.png");
	locateObject(startButton, startScreen, 210, 50);
	showObject(startButton);

	infinityButton = createObject("UI/infinity.png");
	locateObject(infinityButton, startScreen, 510, 50);

	helpButton = createObject("UI/help.png");
	locateObject(helpButton, startScreen, 810, 50);
	showObject(helpButton);

	


	player = createObject("Char/char.png");
	enemy = createObject("Char/enemy_1.png");

	scaleObject(player, 0.4f);
	scaleObject(enemy, 0.4f);

	locateObject(player, gameScreen, 330, 150);
	locateObject(enemy, gameScreen, 830, 150);

	showObject(player);
	showObject(enemy);



	bang = createObject("Effect/bang.png");
	locateObject(bang, gameScreen, 410, 130);


	fadeImage = createObject("BG/fade0.png");
	locateObject(fadeImage, startScreen, 0, 0);

	fadeTimer = createTimer(0.07f);

	frameEff = createObject("Effect/frameEff_1.png");
	locateObject(frameEff, gameScreen, 0, -100);
	scaleObject(frameEff, 2.0f);


	dialChar = createObject("Char/char.png");

	dial = createObject("dial/dial_1.png");
	scaleObject(dial, 1.3f);

	locateObject(dialChar, gameScreen, 200, 100);

	locateObject(dial, gameScreen, 130, 0);



	srand(time(NULL));
	waitTimer = createTimer(5.0f);
	attackTimer = createTimer(0.4f);
	downTimer = createTimer(3.0f);
	nextTimer = createTimer(2.0f);
	endTimer = createTimer(3.0f);
	

	blackScreen = createObject("BG/fade5.png");
	scaleObject(blackScreen, 2.0f);
	locateObject(blackScreen, gameScreen, 0, 0);

	enemyEff = createObject("Effect/enemyEff3_0.png");
	scaleObject(enemyEff, 2.0f);
	locateObject(enemyEff, gameScreen, 300, 0);

	enEffTimer = createTimer(0.04f);

	playerEff = createObject("Effect/atkEff_0.png");
	scaleObject(playerEff, 2.0f);
	locateObject(playerEff, gameScreen, 0, -300);

	plEffTimer = createTimer(0.05f);

	


	screenClicker = createObject("UI/screenClicker.png");
	locateObject(screenClicker, gameScreen, 0, -300);
	scaleObject(screenClicker, 5.0f);
	showObject(screenClicker);


	piano = createSound("SE/piano.mp3");
	tension = createSound("SE/tension.mp3");
	bangSound = createSound("SE/bang.mp3");
	atkSound = createSound("SE/atk1.mp3");
	downSound = createSound("SE/down.mp3");
	buttonSound = createSound("SE/select.ogg");

	effEndTimer = createTimer(1.0f);
	overTimer = createTimer(2.0f);

	startGame(startScreen);
	
}