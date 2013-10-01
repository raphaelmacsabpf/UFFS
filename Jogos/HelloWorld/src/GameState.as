package  
{
	import org.flixel.*;
	import org.flixel.FlxText;
	public class GameState extends FlxState
	{
		override public function create():void 
		{
			
			var b :FlxButton;
			
			b = new FlxButton(30, 30, "Clica ai manolo", sair);
			
			add(b);
			FlxG.mouse.show();
			super.create();
		}
		public function sair() :void {
			var t :FlxText;
			var a :FlxText;
			t = new FlxText(100, 100, 200, "Hello world");
			a = new FlxText(0, FlxG.height - 40, 200, "Minha legenda");
			t.size = 15;
			t.angularAcceleration = 100;
			t.color = 0xFF0000;
			add(t);
			add(a);
			FlxG.log("Oi do console!");
		}
	}

}