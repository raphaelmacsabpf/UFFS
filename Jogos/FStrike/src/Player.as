package  
{
	/**
	 * ...
	 * @author Raphael Machado dos Santos
	 */
	public class Player 
	{
		public var health:int;
		public var maxAmmo:int;
		public var ammo:int;
		public var isReloading:Boolean;
		public var reloadingCounter:Number;
		public function Player() 
		{
			this.health = 100;
			this.maxAmmo = 8;
			this.ammo = 8;
			this.isReloading = 0;
			this.reloadingCounter = 0.0;
		}
		
	}

}