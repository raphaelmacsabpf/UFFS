package 
{
	import flash.events.Event;
	import org.flixel.FlxGame;
	public class Main extends FlxGame 
	{
		public function Main() {
			super(640, 480, GameState
			, 1, 60, 60);
			forceDebugger = true;
		}
	}
}