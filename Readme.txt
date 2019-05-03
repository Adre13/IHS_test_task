Project was created with using Qt 5.12

About:
	The app can parse folder and read .txt files; after it the app create words data base.

Folder "build_for_win" - contains work app for windows 10, you should run test_task_win.exe

Buttons:
	"folder with files" - open dialog window where you can choose folder with .txt files(if current session has loaded data it will rewrite its).
	"Save DB" - if the folder with .txt files was loaded in app you can save this data (you should save data in .txt format).
	"Load DB" - if the data was saved you can load the .txt file in app (but be careful, because you will rewrite your current data in open app).
	"word query" - if you will write "some_word" request in text line and push button, you can see answer in main text window.
	"clear" - clear main text window.