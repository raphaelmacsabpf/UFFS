package  
{
	import flash.events.TextEvent;
	import org.flixel.*;
	import org.flixel.plugin.photonstorm.FlxScrollingText;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Looser extends FlxState
	{
		
		public function Looser() 
		{
			var t:FlxText = new FlxText((FlxG.width / 2) - 200, FlxG.height / 2, 400, "Você perdeu");
			var t2:FlxText = new FlxText(200, 200, 100, "Você fez " + Map.player1.points +" pontos");
			t.alignment = "center";
			t.size = 42;
			add(t);
			add(t2);
			var b:FlxButton = new FlxButton(500, 400, "Try Again", JogarNovamente);
			FlxG.mouse.show();
			add(b);
			
		}
		public function JogarNovamente():void
		{
			FlxG.mouse.hide();
			FlxG.switchState(new Map1Scene1());
		}
		override public function update():void
		{
			super.update();
		}
		
	}

}