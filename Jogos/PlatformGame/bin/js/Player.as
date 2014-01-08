package  
{
	import org.flixel.plugin.photonstorm.*;
	import org.flixel.*;
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Player
	{
		public var mainSprite:MainSpritePlayer;
		public var collisorTop:FlxSprite;
		public var collisorBottom:FlxSprite;
		public var collisorSide:FlxSprite;
		public var spriteGroup:FlxGroup;
		public var lives:int;
		public var points:int;
		public var mapGroup:FlxGroup;
		
		public function Player(pX:Number,pY:Number,mapGroup:FlxGroup) 
		{
			lives = 3;
			points = 0;
			mainSprite = new MainSpritePlayer(pX, pY,this);
			collisorTop = createCollisor("TOP");
			collisorBottom = createCollisor("BOTTOM");
			collisorSide = createCollisor("SIDE");
			spriteGroup = new FlxGroup();
			spriteGroup.add(mainSprite);
			this.mapGroup = mapGroup;
			spriteGroup.add(collisorBottom);
			spriteGroup.add(collisorSide);
			spriteGroup.add(collisorTop);
			
		}
		private function createCollisor(type:String):FlxSprite
		{
			var sprite:FlxSprite
			sprite = new FlxSprite(mainSprite.x, mainSprite.y);
			sprite.loadGraphic(Assets.PLAYERCOLLISOR, true, false, 64, 68);
			sprite.addAnimation("TOP", [1], 1);
			sprite.addAnimation("BOTTOM", [0], 1);
			sprite.addAnimation("SIDE", [2], 1);
			sprite.play(type);
			return sprite;
		}
		public function jump():void
		{
			mainSprite.velocity.y += -3000;
			mainSprite.y -= 10;
		}
		public function update():void
		{
			collisorBottom.x = mainSprite.x;
			collisorBottom.y = mainSprite.y;
			collisorTop.x = mainSprite.x;
			collisorTop.y = mainSprite.y;
			collisorSide.x = mainSprite.x;
			collisorSide.y = mainSprite.y;
			var mapobjs :Array = mapGroup.members;
			for (var i:int = 0; i < mapGroup.length; i++) {
				var mapobj :Block = mapobjs[i];
				
				if (mapobj != null && mapobj.alive && FlxCollision.pixelPerfectCheck(collisorBottom, mapobj))
				{
					mainSprite.collisionBottom();
					break;
				}
			}
			for (var i:int = 0; i < mapGroup.length; i++) {
				var mapobj :Block = mapobjs[i];
				
				if (mapobj != null && mapobj.alive && FlxCollision.pixelPerfectCheck(collisorTop, mapobj))
				{
					mainSprite.collisionTop();
					break;
				}
			}
			for (var i:int = 0; i < mapGroup.length; i++) {
				var mapobj :Block = mapobjs[i];
				
				if (mapobj != null && mapobj.alive && FlxCollision.pixelPerfectCheck(collisorSide, mapobj))
				{
					mainSprite.collisionSide();
					break;
				}
			}
		}
	}

}