<?php
declare(strict_types=1);

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Unit\Assets\Asset\Js;

use Phalcon\Assets\Asset\Js;
use Phalcon\Test\Fixtures\Traits\AssetsTrait;
use UnitTester;

class SetTargetPathCest
{
    use AssetsTrait;

    /**
     * Tests Phalcon\Assets\Asset\Js :: setTargetPath() - js local
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function assetsAssetJsSetTargetPathLocal(UnitTester $I)
    {
        $I->wantToTest('Assets\Asset - setTargetPath() - js local');
        $asset = new Js('js/jquery.js');

        $expected = '/new/path';
        $asset->setTargetPath($expected);
        $this->assetGetTargetPath($I, $asset, $expected);
    }

    /**
     * Tests Phalcon\Assets\Asset\Js :: setTargetPath() - js remote
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function assetsAssetJsSetTargetPathRemote(UnitTester $I)
    {
        $I->wantToTest('Assets\Asset - setTargetPath() - js remote');
        $asset = new Js('https://phalcon.ld/js/jquery.js');

        $expected = '/new/path';
        $asset->setTargetPath($expected);
        $this->assetGetTargetPath($I, $asset, $expected);
    }
}
