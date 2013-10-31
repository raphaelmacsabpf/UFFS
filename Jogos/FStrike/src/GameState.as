package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class GameState extends FlxState
	{
		[Embed(source = "assets/gunfire.mp3", mimeType = "audio/mpeg")] private var gunfire:Class;
		[Embed(source = "assets/reload.mp3", mimeType = "audio/mpeg")] private var reload:Class;
		public var world:World;
		public var character:Character;
		public var sight:Sight;
		public function GameState() 
		{
			world = new World();
			character = new Character();
			sight = new Sight();
			
			add(world);
			add(character);
			add(sight);
		}
		private function weaponShoot()
		{
			FlxG.play(gunfire);
		}
		private function weaponReload()
		{
			FlxG.play(reload);
		}
		override public function update():void
		{
			if (FlxG.mouse.justPressed())
			{
				weaponShoot();
			}
			if (FlxG.keys.justPressed("R"))
			{
				weaponReload();
			}
			super.update();
		}
	}

}