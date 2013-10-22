package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author 
	 */
	public class GameState extends FlxState
	{
		private var personagem:Personagem;
		public function GameState() 
		{
			personagem = new Personagem();
			add(personagem);
			FlxG.mouse.show();
		}
		override public function create():void
		{
			super.create();
		}
		override public function update():void
		{
			if (FlxG.mouse.pressed())
			{
				if (FlxG.mouse.x >= personagem.x)
					personagem.x ++;
				else
					personagem.x --;
				if (FlxG.mouse.y >= personagem.y)
					personagem.y ++;
				else
					personagem.y --;
					
			}
			super.update();
		}
	}

}