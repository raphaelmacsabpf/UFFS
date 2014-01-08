package  
{
	import flash.globalization.CurrencyFormatter;
	import org.flixel.*;
	import org.flixel.plugin.photonstorm.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	
	public class InitialState extends FlxState
	{
		public var mainPlayer:Player;
		public var floor:FlxTileblock;
		public var floor2:FlxTileblock;
		public function InitialState() 
		{
			
		}
		override public function create():void
		{
			FlxG.bgColor = 0xff144954;
			mainPlayer = new Player(100, 100);
			
			floor = new FlxTileblock(0, 408, 900, 32);
			floor.makeGraphic(900, 32, 0xff689c16);
			floor2 = new FlxTileblock(-20, 358 , 1000, 10) ;
			floor2.makeGraphic(1000, 10, 0xff689c16);
			add(mainPlayer);
			add(floor);
			add(floor2);
			FlxG.watch(mainPlayer.acceleration, "x", "ax");
			FlxG.watch(mainPlayer.velocity, "x", "vx");
			FlxG.watch(mainPlayer.velocity, "y", "vy");
			FlxG.watch(mainPlayer, "x", "x");
			FlxG.camera.follow(mainPlayer);
			FlxG.camera.zoom = 1.5;
			super.create();
		}
		override public function update():void
		{
			super.update();
			FlxG.collide(mainPlayer, floor);
			FlxG.collide(mainPlayer, floor2);
		}
	}
}