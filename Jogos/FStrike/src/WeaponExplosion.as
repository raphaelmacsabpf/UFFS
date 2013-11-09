package  
{
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class WeaponExplosion extends FlxSprite
	{
		[Embed(source = "assets/weaponExplosion1.png")] public var ASSET_WEAPONEXPLOSION1:Class;
		public function WeaponExplosion(character:Character) 
		{
			loadGraphic(ASSET_WEAPONEXPLOSION1, true, false, 64, 64);
			addAnimation("fire", [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 24], 120, false);
			if (character.mousePos == 0)
				this.x = (character.x + 206) - 25;
			else
				this.x = character.x-25;
			this.y = character.y - 20;
			this.angle = 360 * FlxG.random();
			play("fire");
		}
		override public function update():void
		{
			if (this.frame == 24)
				this.kill();
			super.update();
		}
		
	}

}