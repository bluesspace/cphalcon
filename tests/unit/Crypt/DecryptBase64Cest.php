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

namespace Phalcon\Test\Unit\Crypt;

use Phalcon\Crypt;
use Phalcon\Crypt\Exception;
use Phalcon\Crypt\Mismatch;
use UnitTester;

class DecryptBase64Cest
{
    /**
     * Tests decrypt without using HMAC
     *
     * @issue  https://github.com/phalcon/cphalcon/issues/13379
     * @author <k@yejune.com>
     * @since  2019-04-16
     */
    public function shouldNotThrowExceptionIfKeyMismatch(UnitTester $I)
    {
        $I->wantToTest(
            'Crypt - decryptBase64() not throwing Exception on key mismatch'
        );

        $crypt = new Crypt();

        $actual = $crypt->decryptBase64(
            $crypt->encryptBase64('le text', 'encrypt key'),
            'wrong key'
        );

        $I->assertNotEmpty($actual);
    }

    /**
     * Tests decrypt using HMAC
     *
     * @issue  https://github.com/phalcon/cphalcon/issues/13379
     * @author                   <k@yejune.com>
     * @since                    2019-04-16
     *
     * @expectedException        Mismatch
     * @expectedExceptionMessage Hash does not match.
     */
    public function shouldThrowExceptionIfHashMismatch(UnitTester $I)
    {
        $I->expectThrowable(
            Exception::class,
            function () {
                $crypt = new Crypt();

                $crypt->useSigning(true);

                $crypt->decryptBase64(
                    $crypt->encryptBase64('le text', 'encrypt key'),
                    'wrong key'
                );
            }
        );
    }

    /**
     * Tests decrypt using HMAC
     *
     * @issue  https://github.com/phalcon/cphalcon/issues/13379
     * @author <k@yejune.com>
     * @since  2019-04-16
     */
    public function shouldDecryptSignedString(UnitTester $I)
    {
        $crypt = new Crypt();

        $crypt->useSigning(true);

        $crypt->setKey('secret');

        $expected  = 'le text';
        $encrypted = $crypt->encryptBase64($expected);
        $actual    = $crypt->decryptBase64($encrypted);

        $I->assertEquals($expected, $actual);
    }
}
