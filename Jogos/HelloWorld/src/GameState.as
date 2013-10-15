package  
{
	import org.flixel.*;
	import org.flixel.FlxText;
	public class GameState extends FlxState
	{
		public var c:Coisa;
		public var ponto:FlxPoint;
		public var aceleracao:Number;
		public var direcaoX:int;
		public var direcaoY:int;
		public var b :FlxButton;
		public var tiro:Coisa;
		override public function create():void 
		{
			c = new Coisa(new FlxPoint(30, 30));
			ponto = new FlxPoint(0.1, 0.1);
			aceleracao = 30;
			direcaoX = 1;
			direcaoY = 1;
	
			
			b = new FlxButton(240, 220, "Atirar", processaTiro);
			FlxG.mouse.show();

			
			add(c);
			add(b);
		}
		override public function update(): void {
			if(c.x+30 >= 320)
				direcaoX = 0;
			if(c.y+30 >= 240)
				direcaoY = 0;
			if(c.x <= 0)
				direcaoX = 1;
			if(c.y <= 0)
				direcaoY = 1;
				
			if(direcaoX)
				c.x = c.x + (ponto.x * aceleracao);
			else
				c.x = c.x - (ponto.x * aceleracao);
			if(direcaoY)
				c.y = c.y + (ponto.y * aceleracao);
			else
				c.y = c.y - (ponto.y * aceleracao);
			if(aceleracao < 30)
				aceleracao += 0.3;
			FlxG.log("Acelecacao eh " + aceleracao);
			
			tiro = new Coisa(new FlxPoint(2,2));
			tiro.x = c.x;
			tiro.y = c.y;
			add(tiro);
			super.update();
		}
		public function processaTiro():void {
			tiro = new Coisa(new FlxPoint(3, 3));
			tiro.x = c.x;
			tiro.y = c.y;
			add(tiro);
			FlxG.log("Atirou");
		}
		/*public function sair() :void {
			var t :FlxText;
			var a :FlxText;
			t = new FlxText(100, 100, 200, "Hello world");
			a = new FlxText(0, FlxG.height - 40, 200, "Minha legenda");
			t.size = 15;
			t.angularAcceleration = 100;
			t.color = 0xFF0000;
			add(t);
			add(a);
			var ponto:FlxPoint = new FlxPoint(2, 2);
			
			FlxG.log("Oi do console!");
		}*/
	}

}