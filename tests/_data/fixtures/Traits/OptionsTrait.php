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

namespace Phalcon\Test\Fixtures\Traits;

use function cacheFolder;
use function env;
use function is_dir;
use function mkdir;

/**
 * Trait DiTrait
 *
 * @package Phalcon\Test\Fixtures\Traits
 */
trait OptionsTrait
{
    /**
     * Get Libmemcached options
     */
    protected function getOptionsLibmemcached(): array
    {
        return [
            'servers' => [
                [
                    'host'   => env('DATA_MEMCACHED_HOST'),
                    'port'   => env('DATA_MEMCACHED_PORT'),
                    'weight' => env('DATA_MEMCACHED_WEIGHT'),
                ],
            ],
        ];
    }

    /**
     * Get Model cache options - Stream
     */
    protected function getOptionsModelCacheStream(): array
    {
        return [
            'lifetime' => 3600,
            'cacheDir' => cacheFolder(),
        ];
    }

    /**
     * Get mysql db options
     */
    protected function getOptionsMysql(): array
    {
        return [
            'host'     => env('DATA_MYSQL_HOST'),
            'username' => env('DATA_MYSQL_USER'),
            'password' => env('DATA_MYSQL_PASS'),
            'dbname'   => env('DATA_MYSQL_NAME'),
            'charset'  => env('DATA_MYSQL_CHARSET'),
        ];
    }

    /**
     * Get postgresql db options
     */
    protected function getOptionsPostgresql(): array
    {
        return [
            'host'     => env('DATA_POSTGRES_HOST'),
            'username' => env('DATA_POSTGRES_USER'),
            'password' => env('DATA_POSTGRES_PASS'),
            'dbname'   => env('DATA_POSTGRES_NAME'),
            'schema'   => env('DATA_POSTGRES_SCHEMA'),
        ];
    }

    /**
     * Get redis options
     */
    protected function getOptionsRedis(): array
    {
        return [
            'host'  => env('DATA_REDIS_HOST'),
            'port'  => env('DATA_REDIS_PORT'),
            'index' => env('DATA_REDIS_NAME'),
        ];
    }

    /**
     * Get Session Stream options
     */
    protected function getOptionsSessionStream()
    {
        if (!is_dir(cacheFolder('sessions'))) {
            mkdir(cacheFolder('sessions'));
        }

        return [
            'savePath' => cacheFolder('sessions'),
        ];
    }

    /**
     * Get sqlite db options
     */
    protected function getOptionsSqlite(): array
    {
        return [
            'dbname' => env('DATA_SQLITE_NAME'),
        ];
    }
}