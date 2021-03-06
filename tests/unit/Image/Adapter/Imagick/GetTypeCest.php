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

namespace Phalcon\Test\Unit\Image\Adapter\Imagick;

use Phalcon\Test\Fixtures\Traits\ImagickTrait;
use UnitTester;

class GetTypeCest
{
    use ImagickTrait;

    /**
     * Tests Phalcon\Image\Adapter\Imagick :: getType()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2016-02-19
     */
    public function imageAdapterImagickGetType(UnitTester $I)
    {
        $I->wantToTest('Image\Adapter\Imagick - getType()');

        $I->skipTest('Need implementation');
    }
}
