#pragma once

bool opus_screen_calibrate_wait = true;
void MagNumb_screen_calibrate_new(void* a) {
	opus_sidesx = 30;//30
	if (GAME_TYPE == GAME_TYPE_INTERMEDIATE)opus_sidesx = 16;
	opus_sidesy = 16;
	if (GAME_TYPE == GAME_TYPE_EASY) { opus_sidesx = 8; opus_sidesy = 8; }
	if (GAME_TYPE == GAME_TYPE_MAX) { opus_sidesx = 49; opus_sidesy = 49; }
	if (GAME_TYPE == GAME_TYPE_99) { opus_sidesx = 99; opus_sidesy = 99; }
	POINT tl, br, reset;
	cout << "board must be reset to new for calibration to work properly. if a game is in session, calibration is impossible\n";
	tl = opus_mouse_define_point("top left land");
	br = opus_mouse_define_point("bottom right land");
	reset = opus_mouse_define_point("reset button");
	opusvs.Set(tl.x - BGA, tl.y - BGA, (br.x - tl.x) + BGA + BGA, (br.y - tl.y) + BGA + BGA);
	
	opusvs.get_screen();
	opusvs.get_buffer();
	opusvs.bufwin_draw();
	pause();
	int x = BGA, y = BGA;
	int landcolor = opusvs.Get_Pixel(x, y);
	int boardercolor, boarderwidth = 0;
	cout << "land color int (minesweeper x EXPECTED:12632256)= " << landcolor << endl;
	int i = 0;
	while (x > 0) {
		boardercolor = opusvs.Get_Pixel(x, y);
		if (boardercolor != landcolor && boardercolor == RGB(255, 255, 255)) {
			x--;
			i = 0;
			while (x - i > 0) {
				if (opusvs.Get_Pixel(x - i, y) == boardercolor)boarderwidth++;
				else break;
				i++;

			}
			break;
		}
		x--;
	}
	x += 3;
	SHOW(boardercolor);
	SHOW(boarderwidth);
	while (y > 0) {
		if (opusvs.Get_Pixel(x + 1, y) != landcolor)break;
		y--;
	}
	//  x,y should be first corner white pixel-
	int xorigin = x, yorigin = y, xwid = 1, ywid = 1;
	int cpwx, cpwy;
	x += 1; y += 1;
	boarderwidth = 1;
	i = 0;
	while (x < 10000) {
		if (opusvs.Get_Pixel(x, y) == boardercolor) {
			x++;
			cpwx = x - xorigin;;
			while (x + i < 10000) {
				if (opusvs.Get_Pixel(x + i, y) == landcolor)break;
				i++; boarderwidth++;
			}
			break;
		}
		x++; xwid++;
	}
	opus_corner_pix = (COLORREF)boardercolor;
	BIG_x = xwid + boarderwidth;
	BIG_y = xwid + boarderwidth;
	cpwx = BIG_x - boarderwidth;
	cpwy = BIG_x - boarderwidth;
	SHOW(BIG_x);
	SHOW(BIG_y);
	SHOW(cpwx);
	SHOW(cpwy);
	opus_CPWx = cpwx;
	opus_CPWy = cpwy;
	opusvs.bufwin_draw();
	pause();
	opusvs.Set(xorigin + (tl.x - BGA) - 1, yorigin + (tl.y - BGA) - 1, BIG_x * opus_sidesx, BIG_y * opus_sidesy);
	trainer.Set(xorigin + (tl.x - BGA) - 1, yorigin + (tl.y - BGA) - 1, BIG_x * opus_sidesx, BIG_y * opus_sidesy);
	_MWOx = xorigin + (tl.x - BGA) - 1;
	_MWOy = yorigin + (tl.y - BGA) - 1;
	opusvs.get_screen();
	opusvs.get_buffer();
	opusvs.bufwin_draw();
	cout << creftostr(opusvs.buf_Get_Pixel(0, 0)) << endl;
	pause();
	for (int ii = 0; ii < opus_sidesy; ii++) {
		for (int nn = 0; nn < opus_sidesx; nn++) {
			if (opusvs.Get_Pixel(nn * BIG_x, ii * BIG_y) != boardercolor) {
				cout << "error at " << nn << ":" << ii << "  found:" << creftostr(opusvs.buf_Get_Pixel(nn * BIG_x, ii * BIG_y)) << endl;
			}

		}
	}
	opusvs.bufwin_draw();
	cout << "make some mooves" << endl;
	pause();
	opusvs.get_screen();
	opusvs.get_buffer();
	opus_reset();
	opus_readboard_buffered();
	opus_color_out();
	opusvs.bufwin_draw();
	opus_global_winout();
	pause();
	opus_screen_calibrate_wait = false;

}
void opus_trainer_screen_thread(void* a) {
	while (opus_screen_calibrate_wait)Sleep(1000);

	cout << "out of calibrate" << endl;

	opus_reset();

	//trainer.Set(opus_trainerx,opus_trainery,opus_trainerw,opus_trainerh);
	//trainer.Set(_MWOx, _MWOy, _MWw, _MWh);
	trainer.get_screen();
	trainer.get_buffer();
	trainer.white_buffer();
	trainer.condc = GetDC(opus_trainer_hwnd);
	val_rect r = opusvs.r;

	cout << "before loop " << endl;
	SetWindowLong(opus_trainer_hwnd, GWL_STYLE, 0);
	::SetWindowPos(opusHWND, HWND_NOTOPMOST, 0, 0, 0, 0,
		SWP_SHOWWINDOW  | SWP_ASYNCWINDOWPOS);
	Sleep(10);
	::SetWindowPos(opus_trainer_hwnd, HWND_TOPMOST, r.X-92, r.Y-92, r.Width+100, r.Height+100,
		SWP_SHOWWINDOW );
	cout << "drawing window moved \n";
	trainer.bufwin_draw(0, 0);
	trainer.bufwin_draw(0, 200);
	trainer.bufwin_draw(200, 0);
	trainer.bufwin_draw(200, 200);
	pause();
	while (1) {
		Sleep(30);
		opus_fast_reset();
		//opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);
		opusvs.get_screen();
		opusvs.get_buffer();

		opus_readboard();
		opus_flags();
		opus_safe_clicks();
		//Magnumb_frame(); 
		opus_flags();
		opus_safe_clicks();
		//Magnumb_basic(); 
		Magnumb_frame();
		opus_flags();
		opus_safe_clicks();

		opus_dedupe_safeclicks();
		trainer.white_buffer();
		trainer.buf_draw_boarder(1);
		opus_trainer_draw_safeclicks();
		opus_trainer_draw_flags();
		trainer.bufwin_draw(100, 100);
	}

}
void opus_main_thread_screen_info(void* a) {

	while (opus_screen_calibrate_wait)Sleep(1000);
	cout << "out of calibratiin\n";
	CLICK_TYPE = 1;
	opus_reset();
	opus_output_info("opusinfo.txt");
	pause();
	int h;
	clrscr();

	int opus_sclick_tot = 0;
	int opus_sclick_totc = 0;
	//startmil();
	short timer = get_new_timer_frame();
	int fasttime = 156;




	while (1) {

		while (1) {
			if (GLOBAL_SLEEP_VALUE)Sleep(GLOBAL_SLEEP_VALUE);
			imgboard.LapUnPause();
			//opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);
			opusvs.get_screen();
			opusvs.get_buffer();
			cout << "got buffer\n";
			//opusvs.get_buffer(opusvs.bmp,opus_GHSw,opus_GHSh);
			imgboard.Lap();

			opus_frames++;
			opus_tframes++;
			procboard.LapUnPause();
			//h = opus_readboard();
			h = opus_readboard_buffered();
			procboard.Lap();
			//opusvs.bufwin_draw();
			//Sleep(1000);
			if (opus_bombcount > 2) {
				if (opus_check_win()) {  // this should practically never happen.

					opus_global_winout();
					if (opus_t_time < fasttime)pause();

				}
				if (DO_PAUSE)pause();
				opus_fast_reset();
				opus_frames = 0;
				opus_restart_game();
				opus_tgames++;
				reset_timer_frame(timer);//startmil();
				continue;
			}
			flags.LapUnPause();
			opus_flags();
			flags.Lap();

			safeclicks.LapUnPause();
			opus_safe_clicks();
			safeclicks.Lap();

			dedupe.LapUnPause();
			opus_dedupe_safeclicks();
			dedupe.Lap();

			if (safe_clicks_len == 0) {
				magnumb.LapUnPause();
				//Magnumb_basic();
				Magnumb_frame();
				opus_flags();
				opus_safe_clicks();
				magnumb.Lap();

				dedupe.LapUnPause();
				opus_dedupe_safeclicks();
				dedupe.Lap();

				if (safe_clicks_len != 0 || Magnum_flagged != 0) {
					cout << "sending clicks" << endl;
					opus_sclick_tot += safe_clicks_len;
					opus_sclick_totc++;
					clicks.LapUnPause();
					while (safe_clicks_len != 0) {
						safe_clicks_len--;
						opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
					}
					opus_t_time = vs_timer_readms(timer);
					clicks.Lap();
					continue;
				}
				break; // game is lost, no moves left  guesses go here.
			}
			opus_sclick_tot += safe_clicks_len;
			opus_sclick_totc++;
			clicks.LapUnPause();
			cout << "sending clicks" << endl;
			while (safe_clicks_len != 0) {

				safe_clicks_len--;
				opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
			}
			clicks.Lap();

			opus_t_time = vs_timer_readms(timer);
		}
		if (opus_check_win()) {
			//t_time=vs_timer_readms(timer);//t_time=endmil();

			opus_global_winout();
			if (opus_t_time < fasttime)pause();
		}
		else {
			//string st = ctostr(opus_tframes) + ".bmp";
			//if(opus_frames>10)opusvs.write_file(st);
			if (opus_frames > 2)opus_games_lost_to_guess++;
		}
		if (DO_PAUSE)pause();
		opus_fast_reset();
		opus_restart_game();
		reset_timer_frame(timer);//startmil();
		opus_tgames++;
		opus_frames = 0;

		//Sleep(1500);   

	}
	pause();


}

void MagNumb_screen_calibrate(void* a) {
	CLICK_TYPE = 2;
	opus_sidesx = 30;//30
	if (GAME_TYPE == GAME_TYPE_INTERMEDIATE)opus_sidesx = 16;
	opus_sidesy = 16;
	if (GAME_TYPE == GAME_TYPE_EASY) { opus_sidesx = 8; opus_sidesy = 8; }
	if (GAME_TYPE == GAME_TYPE_MAX) { opus_sidesx = 49; opus_sidesy = 49; }
	if (GAME_TYPE == GAME_TYPE_99) { opus_sidesx = 99; opus_sidesy = 99; }
	POINT tl, br, reset;
	cout << "board must be reset to new for calibration to work properly. if a game is in session, calibration is impossible\n";
	tl = opus_mouse_define_point("top left land");
	br = opus_mouse_define_point("bottom right land");
	reset = opus_mouse_define_point("reset button");
	opusvs.Set(tl.x - BGA, tl.y - BGA, (br.x - tl.x) + BGA + BGA, (br.y - tl.y) + BGA + BGA);
	opusvs.get_screen();
	opusvs.get_buffer();
	opusvs.bufwin_draw();
	pause();
	int x = BGA, y = BGA;
	int landcolor = opusvs.Get_Pixel(x, y);
	int boardercolor, boarderwidth = 0;
	cout << "land color int (minesweeper x EXPECTED:12632256)= " << landcolor << endl;
	int i = 0;
	while (x > 0) {
		boardercolor = opusvs.Get_Pixel(x, y);
		if (boardercolor != landcolor) {// && boardercolor == RGB(255, 255, 255)
			x--;
			i = 0;
			while (x - i > 0) {
				if (opusvs.Get_Pixel(x - i, y) == boardercolor)boarderwidth++;
				else break;
				i++;

			}
			break;
		}
		x--;
	}
//	x += 3;
	x++;
	SHOW(boardercolor);
	SHOW(boarderwidth);
	while (y > 0) {
		if (opusvs.Get_Pixel(x + 1, y) != landcolor)break;
		y--;
	}
	//  x,y should be first corner white pixel-
	int xorigin = x, yorigin = y, xwid = 1, ywid = 1;
	int cpwx, cpwy;
	x += 1; y += 1;
	boarderwidth = 1;
	i = 0;
	while (x < 10000) {
		if (opusvs.Get_Pixel(x, y) == boardercolor) {
			x++;
			cpwx = x - xorigin;;
			while (x + i < 10000) {
				if (opusvs.Get_Pixel(x + i, y) == landcolor)break;
				i++; boarderwidth++;
			}
			break;
		}
		x++; xwid++;
	}
	x = xorigin + 1;
	SHOW(boarderwidth);
	cout << "looking for 255,255,255:" << creftostr(boardercolor) << endl;
	while (y < 100) {
		if (opusvs.Get_Pixel(x, y) == boardercolor) {
			y++;
			cpwy = y - yorigin;
			while (y < 10000) {
				if (opusvs.Get_Pixel(x + 3, y) == landcolor)break;
				y++;// ywid++;
			}
			break;
		}
		cout << "x: " << x << " y:" << y << " color: " << creftostr(opusvs.Get_Pixel(x, y)) << endl;
		y++; ywid++;
	}
	opus_corner_pix = (COLORREF)boardercolor;
	BIG_x = xwid + boarderwidth;
	BIG_y = ywid + boarderwidth;
	cpwx -= boarderwidth;
	cpwy -= boarderwidth;
	SHOW(BIG_x);
	SHOW(BIG_y);
	SHOW(cpwx);
	SHOW(cpwy);
	opus_CPWx = cpwx;
	opus_CPWy = cpwy;
	opusvs.bufwin_draw();
	pause();

	opusvs.Set(xorigin + (tl.x - BGA) - 1, yorigin + (tl.y - BGA) - 1, BIG_x * opus_sidesx, BIG_y * opus_sidesy);

	opusvs.get_screen();
	opusvs.get_buffer();
	opusvs.white_buffer();

	opusvs.bufwin_draw();
	cout << creftostr(opusvs.buf_Get_Pixel(0, 0)) << endl;
	pause();
	for (int ii = 0; ii < opus_sidesy; ii++) {
		for (int nn = 0; nn < opus_sidesx; nn++) {
			if (opusvs.Get_Pixel(nn * BIG_x, ii * BIG_y) != boardercolor) {
				cout << "error at " << nn << ":" << ii << "  found:" << creftostr(opusvs.buf_Get_Pixel(nn * BIG_x, ii * BIG_y)) << endl;
			}

		}
	}
	opusvs.bufwin_draw();
	cout << "make some mooves" << endl;
	pause();
	opusvs.get_screen();
	opusvs.get_buffer();
	opus_reset();
	opus_readboard();
	opus_color_out();
	opusvs.bufwin_draw();
	pause();
	//BIGx = xwid + (boarderwidth * 2); // this may need to be -1, or possibly just keep x/ywid init to 0 
	//BIGy = ywid + (boarderwidth * 2);
	//only works on board with 0,0 as land
	//get top left, bottom right squares from user or scrape
	//scrape board prototype.
	// search left/right from userpoint till not land color -> cpwx??
	// search up/down from userpoint till not land color -> cpwy??
	//set bigx,bigy -- start at 0,1 or 1,0 and trace right/down till next transition, then till next land color
	// get 0,0 from these searches
	//check 0,0 for cornercolor
	// reset vs and check new alignment. 
	// check 9x9 origin move for errors
	//if no errors, return that calibration
	// set click type to xp style. 
}

// refactor this shithole here. 
void opus_main_thread_screen_info2022(void* a) {
	while (opus_screen_calibrate_wait)Sleep(1000);
	bool lastclick_pattern = 0;
	opus_reset();
	opus_output_info("opusinfo.txt");
	pause();
	int h;
	clrscr();

	int opus_sclick_tot = 0;
	int opus_sclick_totc = 0;
	//startmil();
	short timer = get_new_timer_frame();
	int fasttime = 120;// 143;

	ValScreen vshwndsearch;


	int x, y, w, hh;
	int xxx = 0, yyy = 0;
	while (1) {

		while (1) {
			if (DO_PAUSE)pause();
			if (GLOBAL_SLEEP_VALUE)Sleep(GLOBAL_SLEEP_VALUE);
			imgboard.LapUnPause();
			opusvs.get_hwnd_screen(opusHWND, opus_GHSx, opus_GHSy, opus_GHSw, opus_GHSh);
			opusvs.get_buffer();
			//opusvs.get_buffer(opusvs.bmp,opus_GHSw,opus_GHSh);
			imgboard.Lap();

			Magnum_flagged = 0;
			opus_frames++;
			opus_tframes++;
			procboard.LapUnPause();
			//h = opus_readboard();
			h = opus_readboard_buffered();
			procboard.Lap();
			//opusvs.bufwin_draw();
			//Sleep(1000);
			if (opus_bombcount > 2) {
				Sleep(1);
				opusHWND = vshwndsearch.find_Window("Minesweeper X", x, y, w, hh);
				if (opus_check_win()) {  // this should practically never happen.

					opus_global_winout();
					if (opus_t_time < fasttime)pause();
					cout << "won after finding bombcount... fix me\n";
					pause();

				}
				if (DO_PAUSE)pause();
				//cout << "game lost to bombs" << endl;
				opus_games_lost_to_bomb++;
				if (lastclick_pattern) {
					cout << "last click was pattern loss\n";
					//pause();
					opus_games_lost_to_pattern++;
				}
				if (OPUS_last_click_guess) {
					//cout << "last click was guess loss\n";
					opus_games_lost_to_guessing++;
				}

				opus_bombcount = 0;
				//goto dorestart;
				opus_fast_reset();
				opus_frames = 0;
				opus_restart_game();
				opus_restart_game();
				opus_tgames++;
				reset_timer_frame(timer);//startmil();

				continue;
			}
		reparse:
			lastclick_pattern = 0;
			flags.LapUnPause();
			opus_flags();
			flags.Lap();

			safeclicks.LapUnPause();
			opus_safe_clicks();
			safeclicks.Lap();
			flags.LapUnPause();
			opus_flags();
			flags.Lap();

			safeclicks.LapUnPause();
			opus_safe_clicks();
			safeclicks.Lap();
			dedupe.LapUnPause();
			opus_dedupe_safeclicks();
			dedupe.Lap();

			if (safe_clicks_len == 0) {
				if (opus_frames > 1000) {
					opus_failed_frames++;
					opus_reset();
				}
				magnumb.LapUnPause();
				//Magnumb_basic();
				Magnumb_frame();
				//opus_flags();
				//opus_safe_clicks();
				magnumb.Lap();

				dedupe.LapUnPause();
				opus_dedupe_safeclicks();
				dedupe.Lap();

				if (safe_clicks_len != 0 || Magnum_flagged != 0) {
					lastclick_pattern = 1;
					OPUS_last_click_guess = false;
					opus_sclick_tot += safe_clicks_len;
					opus_sclick_totc++;
					clicks.LapUnPause();
					while (safe_clicks_len != 0) {
						safe_clicks_len--;
						opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
					}
					opus_t_time = vs_timer_readms(timer);
					clicks.Lap();
					continue;
				}
				magnumbfrontier.LapUnPause();
				MagnumbFrontiers();
				magnumbfrontier.Lap();

				//pause();
				if (Magnumb_Probecount > 0) {
					//pause();
					opus_sclick_tot += safe_clicks_len;
					opus_sclick_totc++;
					clicks.LapUnPause();
					OPUS_last_click_guess = false;
					while (safe_clicks_len != 0) {
						safe_clicks_len--;
						opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
					}
					clicks.Lap();
					continue;
				}
				else if (Magnumb_Minecount > 0) {
					goto reparse;  // could get rid of this with a while(1) loop, break statement right at the end, continue here.......
					//continue; // found a mine, reparse from the start
				}
				else {
					//  no moves/mines left to find.   guesses go here.
					if (opus_check_win()) goto winout;  //could replace this with a latch and a break;
					if (OPUS_DOGUESSES == 1) {

						magnumb_guess_fill();
						magnumb_guess_parse(xxx, yyy, 0);
						//cout << "Heuristic found a guess at x y:" << xxx << " " << yyy << "\n";
						Sleep(500);
						opus_doclick(xxx, yyy, 0);
						Sleep(500);
						OPUS_last_click_guess = true;
						OPUS_total_guesses++;
						//continue;// goto reparse;
					}
					else if (OPUS_DOGUESSES == 2) {

						xxx = MagnumbFrontiers_guess[0];
						yyy = MagnumbFrontiers_guess[1];
						if (MagnumbFrontiers_lastguess[0] == xxx && MagnumbFrontiers_lastguess[1] == yyy) {  //&& MagnumbFrontiers_callcount - MagnumbFrontiers_lastcallcount < 4
							//cout << "breaking out, same guess twice\n";
							break; // need more attuned guessing if board isn't solved.
							// surrounded squares currently unsolved
						}
						MagnumbFrontiers_lastguess[0] = xxx;
						MagnumbFrontiers_lastguess[1] = yyy;
						opus_guessed_this_game = true;
						cout << "Magnumb FRontiers found a guess at x y:" << xxx << " " << yyy << "                  \r";
						//cout << "Magnumb Frontiers callcount: " << MagnumbFrontiers_callcount << "\n";
						//Sleep(200);
						opus_doclick(xxx, yyy, 0);
						//Sleep(200);
						OPUS_last_click_guess = true;
						MagnumbFrontiers_Cumulative_guess_assessment += MagnumbFrontiers_guess_probability;
						OPUS_total_guesses++;
						//continue;
					}
					else  break; // not guessing, restart.
				}

			}// if safeclicklen==0;
			opus_sclick_tot += safe_clicks_len;
			opus_sclick_totc++;
			clicks.LapUnPause();

			while (safe_clicks_len != 0) {

				safe_clicks_len--;
				opus_doclick(safe_clicks[safe_clicks_len].x, safe_clicks[safe_clicks_len].y, 0);
			}
			clicks.Lap();

			opus_t_time = vs_timer_readms(timer);
		}
		if (opus_bombcount > 0) {
			//cout << "writing bombboard.bmp";
			//string temp = "bombboard" + ctostr(opus_tframes) + ".bmp";
			//opusvs.write_file(temp);//ctostr(opus_tframes) + 
		}
		if (opus_check_win()) {
			//t_time=vs_timer_readms(timer);//t_time=endmil();
		winout:
			opus_global_winout();
			Sleep(50);
			HWND hw = vshwndsearch.find_Window("Congratulations", x, y, w, hh);
			// detection works... showing/clicking the toolwindow doesn't  
			if (hw) {
				Sleep(500);
				ShowWindow(hw, SW_SHOW);
				ShowWindow(hw, SW_HIDE);
				SetWindowPos(hw, nullptr, 100, 100, 0, 0, SWP_NOSIZE);
				opusStayOnTop(hw);
				cout << "fastest time window detected\n";
				pause();
				SendMessage(hw, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(220, 150));
				SendMessage(hw, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(220, 150));
				//click at 220,150
				Sleep(200);
				//"Best Times" window at 350/200
				hw = vshwndsearch.find_Window("Best Times", x, y, w, hh);
				opusStayOnTop(hw);
				Sleep(200);
				SendMessage(hw, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(350, 200));  // this seems to work
				SendMessage(hw, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(350, 200)); // all difficulties

				pause();
			}
			//pause();
			if (opus_t_time < fasttime) {
				cout << "fastest time detected\n";
				pause();
			}
		}
		else {
			//string st = ctostr(opus_tframes) + ".bmp";
			//if(opus_frames>10)opusvs.write_file(st);
			if (opus_frames > 2) {
				opus_games_lost_to_guess++;  //change this up a bit.
				//cout << "writing board.bmp";
				//string temp = ctostr(opus_tframes) + "board.bmp";
				//opusvs.write_file(temp);//ctostr(opus_tframes) + 
			}
			else opus_games_lost_to_first_click++;
		}
	dorestart:
		if (DO_PAUSE)pause();
		opus_fast_reset();
		reset_timer_frame(timer);
		opus_restart_game();
		opus_tgames++;
		opus_frames = 0;

		//Sleep(1500);   

	}
	pause();


}