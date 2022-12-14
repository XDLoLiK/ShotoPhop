#include "main.hpp"

int main()
{
	App app("ShotoPhop");

	Frame mainFrame({0, 0, 1920, 1080});
	mainFrame.setBackground("./skins/bg.png");
	mainFrame.show();

	Canvas canvas({400, 140, 1220, 820});
	canvas.show();

	Toolbar* toolbar = new Toolbar({0, 40, 60, 1080 - 40});
	toolbar->addTools(PluginManager::getPluginManager()->getTools());
	toolbar->show();

	Frame menuFrame({0, 0, 1920, 40});
	menuFrame.setBackground(Color(251, 224, 243, 140));
	menuFrame.setFrameColor(Color(251, 224, 243, 140));
	menuFrame.show();

	ContextButton<App> closeButton("Exit", {0, 0, 100, 40});
	closeButton.setContext(&app);
	closeButton.setAction(closeApp);
	closeButton.setFrameColorDefault(Color(231, 178, 212, 255));
	closeButton.setFrameColorHover(Color(185, 130, 183, 255));
	closeButton.setBackgroundDefault(Color(231, 178, 212, 255));
	closeButton.setBackgroundHover(Color(185, 130, 183, 255));
	closeButton.setShortcut(SDLK_e);
	closeButton.show();

	DropList fileList("File", {100, 0, 100, 40});
	fileList.setShortcut(SDLK_f);
	fileList.show();

	ContextButton<Canvas> saveButton("Save", {0, 0, 360, 40});
	saveButton.setContext(&canvas);
	saveButton.setAction(canvasSave);
	fileList.addEntry(&saveButton);

	ContextButton<Canvas> saveAsButton("Save As", {0, 0, 360, 40});
	saveAsButton.setContext(&canvas);
	saveAsButton.setAction(canvasSaveAs);
	fileList.addEntry(&saveAsButton);

	ContextButton<Canvas> openButton("Open", {0, 0, 360, 40});
	openButton.setContext(&canvas);
	openButton.setAction(canvasOpen);
	fileList.addEntry(&openButton);

	DynamicWindow* colorChoiseWin = new DynamicWindow({100, 100, 600, 400});
	colorChoiseWin->setBackground(Color(77, 77, 77, 255));
	ColorPicker colorPicker({0, 0, 400, 400}, colorChoiseWin);

	ContextButton<ColorPicker> fgChooseButton("Forground", {410, 40, 180, 40}, white, colorChoiseWin);
	fgChooseButton.setContext(&colorPicker);
	fgChooseButton.setAction(pickForgroundColor);
	fgChooseButton.setBackgroundDefault(Color(120, 120, 120, 255));
	fgChooseButton.setBackgroundHover(Color(100, 100, 100, 255));
	fgChooseButton.setFrameColorDefault(Color(120, 120, 120, 255));
	fgChooseButton.setFrameColorHover(Color(100, 100, 100, 255));

	ContextButton<ColorPicker> bgChooseButton("Background", {410, 100, 180, 40}, white, colorChoiseWin);
	bgChooseButton.setContext(&colorPicker);
	bgChooseButton.setAction(pickBackgroundColor);
	bgChooseButton.setBackgroundDefault(Color(120, 120, 120, 255));
	bgChooseButton.setBackgroundHover(Color(100, 100, 100, 255));
	bgChooseButton.setFrameColorDefault(Color(120, 120, 120, 255));
	bgChooseButton.setFrameColorHover(Color(100, 100, 100, 255));

	ContextButton<DynamicWindow> colorButton("Color", {200, 0, 100, 40});
	colorButton.setContext(colorChoiseWin);
	colorButton.setAction(showWin);
	colorButton.setShortcut(SDLK_c);
	colorButton.show();

	ContextButton<DynamicWindow>* toolButton = new ContextButton<DynamicWindow>("Tool", {300, 0, 100, 40});
	toolButton->setContext(PluginManager::getPluginManager()->getCanvas());
	toolButton->setAction(showCanvas);
	toolButton->setShortcut(SDLK_t);
	toolButton->show();

	return app.run();
}
