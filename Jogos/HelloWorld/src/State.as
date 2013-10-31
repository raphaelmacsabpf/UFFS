package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author 
	 */
	public class State extends FlxState
	{
		
		public function State() 
		{
			
		}
		private var caveira: Caveira;
		override public function create():void 
		{
			caveira = new Caveira();
			add(caveira);
			FlxG.mouse.show();
			super.create();
		}
		override public function update():void
		{
			caveira.x = FlxG.mouse.x;
			caveira.y = FlxG.mouse.y;
			if (FlxG.mouse.pressed())
				add(new Ship(caveira.x,caveira.y));
			super.update();
		}
	}

}